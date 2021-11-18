/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerRequest.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:35:02 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 00:47:55 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandlerRequest.hpp"

HandlerRequest::HandlerRequest(BuilderRequest &	builder) :
	_client(0),
	_builder(builder),
	_account(0)
{}

HandlerRequest::HandlerRequest(HandlerRequest const & src) :
	_client(src._client),
	_builder(src._builder),
	_account(src._account)
{}

HandlerRequest::~HandlerRequest(void)
{
	
}

HandlerRequest &
HandlerRequest::operator=(HandlerRequest const & rhs)
{
	if (this != &rhs){
		_client = rhs._client;
		_account = rhs._account;
	}
	return *this;
}

HandlerRequest &
HandlerRequest::set_client(Client * client)
{
	_client = client;
	return *this;
}

Request &
HandlerRequest::get_request()
{
	return (_client->get_request());
}

const Request &
HandlerRequest::get_request() const
{
	return (_client->get_request());
}

Server &
HandlerRequest::get_server()
{
	return (_client->get_server());
}

ClientSocket &
HandlerRequest::get_client_socket()
{
	return (_client->get_socket_struct());
}

size_t
HandlerRequest::get_account() const
{
	return (_account);
}

int
HandlerRequest::handle(Client & client, servers & v_servers)
{
	set_client(&client);
	// std::cout << "state : " << client.get_state() << std::endl;
	try
	{
		switch (_client->get_state())
		{
		case Client::READ_HEADER:
				read_header(v_servers);
			break;
		case Client::STRATEGY:
			if ((_client->get_revent() & POLLIN) != 0)
				_client->get_socket_struct().get_reader().fill_buffer();
			_client->do_strategy(*_client);
			break;
		case Client::SEND_RESPONSE:
			_client->send(_client->get_socket());
			break;
		case Client::END:
			return (clean());
			// _client->clean_reponse();
			// get_request().reset();
			// _account++;
			// return (_client->get_socket());
		default:
			break;
		}
	}
	catch(const AReaderFileDescriptor::ReadError& e)
	{
		return (clean());
	}
	catch(const AReaderFileDescriptor::WriteError& e)
	{
		return (clean());
	}
	return (-1);
}

void 
HandlerRequest::parse()
{
	std::string				line = "";
	AReaderFileDescriptor &	reader	= get_client_socket().get_reader();
	std::string &			chunck	= reader.get_chunck();
	int						ret		= 0;
	
	_builder.set_message(&get_request());
	if (reader.has_all_headers())
	{
		reader.cut_header();
		while (chunck.find("\r\n\r\n") != std::string::npos)
		{
			line = chunck.substr(0, chunck.find("\r\n")) + "\r";
			_builder.parse_request(line);
			chunck = chunck.substr(chunck.find("\r\n") + 2);
		}
		get_request().set_header_lock(true);
	}
	else
	{
		if ((_client->get_revent() & POLLIN) != 0)
		{
			try
			{
				ret = reader.next_read();
			}
			catch(const std::exception& e)
			{
				_client->set_close(true);
			}
			reader.concatenation();
		}
	}
}

void
HandlerRequest::read_header(servers & v_servers)
{
	try{
		// if ((_client->get_revent() & POLLIN) != 0)
		this->parse();
		if (!is_complete())
			return;
		this->check_host(v_servers);
		check_body_size(*_client);
		check_method_exist(*_client);
		if (get_server().is_directory(get_request()))
			this->set_index();
		std::string extension = Extension::get_extension(get_request().get_path());
		if (_client->get_server().get_return_list().size())
			_client->set_strategy(new StrategyReturn(get_server().get_return_list().front()));
		else if (get_server().has_cgi(extension))
			_client->set_strategy(new StrategyCGI(get_server().get_cgi(extension)));
		else
		{
			if (get_server().is_directory(get_request()))
			{
				if (!get_server().get_auto_index())
					_client->set_strategy(new StrategyError(403));
				else
					_client->set_strategy(new StrategyIndex());
			}
			else
				_client->set_strategy(new StrategyAccept());
		}
		
	}
	catch (BuilderMessage::BadRequest &e)
	{
		_client->set_strategy(new StrategyError(400));
	}
	catch (BuilderRequest::BadHttpVersion &e)
	{
		_client->set_strategy(new StrategyError(505));
	}
	catch (BuilderRequest::MethodNotImplemented &e)
	{
		_client->set_strategy(new StrategyError(501));
	}
	catch (BodyTooLong &e)
	{
		_client->set_strategy(new StrategyError(413));
	}
	catch (MethodNotAllowed &e)
	{
		_client->set_strategy(new StrategyError(405));
	}
}

int
HandlerRequest::clean()
{
	_client->clean_reponse();
	get_request().reset();
	_account++;
	return (_client->get_socket());
}

void
HandlerRequest::set_index()
{
	Request &	request		= get_request();
	Server	&	server		= get_server();
	std::string	actual_path	= request.get_path();
	std::string	slash		= "";

	if (!actual_path.empty() && actual_path[actual_path.length() - 1] != '/')
		slash = "/";
	request.set_path(actual_path + slash + server.get_index(actual_path));
}

bool
HandlerRequest::is_complete() const
{
	return (get_request().get_header_lock());
}

void
HandlerRequest::check_host(servers & vector)
{
	Request &		request			= get_request();
	ServerSocket &	server_socket	= _client->get_server_socket();
	int				port			= server_socket.get_port();
	std::string		host;
	size_t			find;

	if (request.has_header("Host"))
	{
		host = request.get_header("Host");
		find = host.find(":", 0);
		if(find  != std::string::npos)
			host = host.substr(0, find);
		if (host != get_server().get_name())
		{
			servers::iterator ite = vector.end();
		
			for (servers::iterator it = ++(vector.begin()); it != ite; it++)
			{
				if ((*it).get_name() == host && (*it).get_server_socket(port, server_socket.get_ip()))
				{
					_client->set_server(&(*it));
					_client->set_server_socket(it->get_server_socket(port, server_socket.get_ip()));
					break;
				}
			}
		}
	}
	else
		throw BuilderMessage::BadRequest();
}

void
HandlerRequest::check_body_size(Client const & client) const
{
	const Server &	server	= client.get_server();
	const Request &	request	= client.get_request();
	size_t			length	= 0;

	if (request.has_header("Content-Length"))
		length = request.get_header<size_t>("Content-Length");
	if (server.get_client_max_body_size() < length)
		throw BodyTooLong();
}

void
HandlerRequest::check_method_exist(Client const & client) const
{
	const Server &					server	= client.get_server();
	const Request &					request	= client.get_request();
	const std::list<AMethod *> &	methods	= server.get_list_method();
	std::list<AMethod *>::const_iterator	ite	= methods.end();

	for (std::list<AMethod *>::const_iterator it = methods.begin(); it != ite; it++)
	{
		if (request.get_method()->get_name() == (*it)->get_name())
			return ;
	}
	throw MethodNotAllowed();
}