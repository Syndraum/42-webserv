/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:51 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/16 20:03:14 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"

Core::Core(void) :
_worker(3)
//_maxfd(-1),
{
	_SIZE_SOCK_ADDR = sizeof(struct sockaddr_in);
	_methods
		.add_method(new MethodGet())
		.add_method(new MethodDelete())
		;
	_br.set_library(&_methods);
}

Core::Core(Core const & src)
{
	*this = src;
}

Core::~Core() {}

Core &
Core::operator=(Core const & rhs)
{
	if (&rhs != this)
		this->_worker = rhs._worker;
	return *this;
}

void
Core::start()
{
	std::vector<int> active_socket;
	try{

		for (size_t i = 0; i < _servers.size(); i++)
		{
			_servers[i].start(_worker);
		}
	}
	catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "test" << std::endl;

		return ;
	}
print();
	_pfdh.init(_servers);
	while (true)
	{
		poll(&(_pfdh.get_all_pfd().front()), _pfdh.get_all_pfd().size(), 60000);
		_accept_connection();
		_handle_request_and_detect_close_connection();
	}
}

void
Core::add_server(Server & server)
{
	_servers.push_back(server);
}

Server &
Core::add_server()
{
	_servers.push_back(Server());
	return(_servers.back());
}

Server	const &
Core::get_server(int index) const
{
	return (_servers.at(index));
}

int	
Core::get_worker(void) const
{
	return (_worker);
}

Core &
Core::set_worker(int worker)
{
	_worker = worker;
	return(*this);
}

void
Core::set_extension(Extension * extension)
{
	_extension = extension;
}

void
Core::print() const
{
	for (size_t i = 0; i < _servers.size(); i++)
	{
		_servers[i].print();
	}
	if (_servers.size() == 0)
		std::cout << "no Server found \n";
}

void
Core::_accept_connection()
{
	int new_socket = -1;
	int one = 1;

	for (size_t i = 0; i < _servers.size(); i++)
	{
		Server & server = _servers[i];
		for (Server::port_map::iterator it = server.get_server_socket().begin(); 
				it != server.get_server_socket().end(); it++)
		{
			ServerSocket & server_socket = it->second;
			int fd = server_socket.get_socket();

			if (_pfdh.get_all_pfd()[server_socket.get_id()].revents == _pfdh.get_all_pfd()[server_socket.get_id()].events)
			{
				_client.push_back(ClientSocket(server));
				ClientSocket & cs = _client.back();
				if ((new_socket = accept(fd, (struct sockaddr *)&cs.get_address() , reinterpret_cast<socklen_t*>(&_SIZE_SOCK_ADDR))) < 0)
				{
					perror("accept failed");
					exit(EXIT_FAILURE);
				}
				setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
				std::cout << "New connection, socket fd is " << new_socket << ", socket server :" << fd << std::endl;
				cs.set_socket(new_socket);
				std::cout << "Adding to list of sockets as " << _client.size() << std::endl;


				_pfdh.add_clients_pfd(new_socket, POLLOUT);
			}
		}
		
	}
}

void
Core::_handle_request_and_detect_close_connection()
{
	for (client_vector::iterator it = _client.begin(); it != _client.end(); it++)
	{
		Request *	request	= &it->get_request();
		Server &	server	= (*it).get_server();
		Response	response(*request, 200);

		// (*it).get_server().print();
		//Check if it was for closing , and also read the 
		//incoming message 
		try{
//			std::cout << "_is_first_line: " << request->get_first_line() << std::endl;
			_br.set_request(request);
			_br.parse_request(*it);
			request->set_path(request->get_path() + server.get_index(request->get_path()));
			if (server.is_directory(*request))
				if (!server.get_auto_index())
					response.set_error(403);
				else
				{
					response
						.set_code(200)
						.set_body(server.get_index_page(*request))
						.add_header("Content-type", "text/html");
				}
			else
			{
				request->set_path(server.get_full_path(request->get_path()));
				// std::cout << "PATH : " << request->get_path() << std::endl;
				request->action(response);
			}
		}
		catch (BuilderRequest::BadRequest &e)
		{
			response.set_code(400).clear_header();
		}
		catch (BuilderRequest::BadHttpVersion &e)
		{
			response.set_code(505).clear_header();
		}
		catch (BuilderRequest::MethodNotImplemented &e)
		{
			response.set_code(501).clear_header();
		}
		catch (BuilderRequest::NoRequest &e)
		{
//			std::cout << "test NoRequest" << std::endl;
			continue;
		}
		catch (Request::NoMethod &e)
		{
//			std::cout << "test NoMethod" << std::endl;
			std::cout << "Client " << it->get_socket() << " disconnected" << std::endl;  

			_pfdh.erase(it->get_socket());
			close( it->get_socket() );  
			_client.erase(it);  
			break;
		}
		std::cout << "write in Socket: " << it->get_socket() << std::endl;
		response.send_response(it->get_socket());

		_pfdh.erase(it->get_socket());
		close( it->get_socket() );  
		_client.erase(it);  
		break;
	}
}
