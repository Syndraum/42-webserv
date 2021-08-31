#include "HandlerRequest.hpp"

HandlerRequest::HandlerRequest(
	BuilderRequest &	builder
	) :
		_client(0),
		_builder(builder)
{}

HandlerRequest::HandlerRequest(HandlerRequest const & src) :
	_client(src._client),
	_builder(src._builder)
{}

HandlerRequest::~HandlerRequest(void)
{
	
}

HandlerRequest &
HandlerRequest::operator=(HandlerRequest const & rhs)
{
	if (this != &rhs){
		_client = rhs._client;
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

HandlerRequest::clients_iterator
HandlerRequest::handle(clients & v_clients, servers & v_servers)
{
	for (clients_iterator it = v_clients.begin(); it != v_clients.end(); it++)
	{
		set_client(&(*it));
		try{
			this->parse();
			if (!is_complete())
				continue;
			this->check_host(v_servers);
			check_body_size(*it);
			check_method_exist(*it);
			this->set_index();
			std::string extension = Extension::get_extension(get_request().get_path());
			if (it->get_server().get_return_list().size())
				_handler_response.set_strategy(new StrategyReturn(get_server().get_return_list().front()));
			else if (get_server().has_cgi(extension))
				_handler_response.set_strategy(new StrategyCGI(get_server().get_cgi(extension)));
			else
			{
				if (get_server().is_directory(get_request()))
				{
					if (!get_server().get_auto_index())
						_handler_response.set_strategy(new StrategyError(403));
					else
						_handler_response.set_strategy(new StrategyIndex());
				}
				else
					_handler_response.set_strategy(new StrategyAccept());
			}
			
		}
		catch (BuilderMessage::BadRequest &e)
		{
			_handler_response.set_strategy(new StrategyError(400));
		}
		catch (BuilderRequest::BadHttpVersion &e)
		{
			_handler_response.set_strategy(new StrategyError(505));
		}
		catch (BuilderRequest::MethodNotImplemented &e)
		{
			_handler_response.set_strategy(new StrategyError(501));
		}
		catch (BodyTooLong &e)
		{
			_handler_response.set_strategy(new StrategyError(413));
		}
		catch (MethodNotAllowed &e)
		{
			_handler_response.set_strategy(new StrategyError(405));
		}
		_handler_response.do_strategy(*_client);
		_handler_response.send(it->get_socket());
		_handler_response.reset();
		get_request().reset();
		return (it);
	}
	return (v_clients.end());
}

void 
HandlerRequest::parse()
{
	std::string		line;
	int				gnl_ret = 1;
	
	_builder.set_message(&get_request());
	while (gnl_ret && (gnl_ret = get_client_socket().get_reader().get_next_line(line)))
	{
		if (gnl_ret == -1)
			return ;
		// std::cout << "line: " << line << std::endl;
		line += "\r";
		_builder.parse_request(line);
		if (get_request().get_header_lock())
		{
			if (!get_request().has_header("Content-Length"))
			{
				// std::cout << "No Content-Length" << std::endl;
				get_client_socket().get_reader().read_until_end(line);
				//std::cout << "_buffer: " << _buffer << std::endl;
			}
			else
			{
				// std::cout << "Content-Length : " << get_request().get_header("Content-Length") << std::endl;
				get_client_socket().get_reader().read_body(line, std::atoi(get_request().get_header("Content-Length").c_str()));
				get_request().set_body(line);
			}
			get_request().set_body_lock(true);
			get_client_socket().get_reader()._reset_buffer();
			gnl_ret = 0;
		}
	}
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
	return (get_request().get_header_lock() && get_request().get_body_lock());
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
				if ((*it).get_name() == host && (*it).has_port(port))
				{
					_client->set_server(&(*it));
					_client->set_server_socket(&(it->get_server_socket(port)));
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
		std::cout << "name : " << (*it)->get_name() << std::endl;
		if (request.get_method()->get_name() == (*it)->get_name())
			return ;
	}
	throw MethodNotAllowed();
}