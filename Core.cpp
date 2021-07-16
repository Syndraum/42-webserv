/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:51 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/16 12:02:28 by roalvare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"

Core::Core(void) :
_worker(3),
//_maxfd(-1),
_nb_active(0)
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
	int fd;
	std::vector<int> active_socket;

	// this has to be something we can keep and update
	_fds = new struct pollfd[10];

	for (size_t i = 0; i < _servers.size(); i++)
	{
		_servers[i].start(_worker);
	}
	print();
	while (true)
	{

		// value given to poll (nbFds)
		_nb_fds = 0;
		for (size_t i = 0; i < _servers.size(); i++)
		{
			Server & server = _servers[i];
			for (Server::port_map::iterator it = server.get_server_socket().begin(); 
				it != server.get_server_socket().end(); it++)
			{
				ServerSocket & server_socket = it->second;

				fd = server_socket.get_socket();
				_fds[_nb_fds].fd = fd;
				_fds[_nb_fds].events = POLLIN;
				_fds[_nb_fds].revents = 0;
				server_socket.set_id(_nb_fds);
				_nb_fds++;
			}
		}
		for (size_t i = 0; i < _client.size(); i++)
		{
			fd = _client[i].get_socket();
			_fds[_nb_fds].fd = fd;
			_fds[_nb_fds].events = POLLOUT;
			_fds[_nb_fds].revents = 0;
			_client[i].set_id(_nb_fds);
			_nb_fds++;
		}
		_nb_active = poll(_fds, _nb_fds, 60000);
		_accept_connection();

		_handle_request_and_detect_close_connection();
//		_cdai_dirty_function();

		// detect and set serversocket from POLLIN/POLLOUT to 0
		_detect_reset_server_poll_fd();
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

			if (_fds[server_socket.get_id()].revents == _fds[server_socket.get_id()].events)
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
			}
		}
		
	}
}

void
Core::_handle_request_and_detect_close_connection()
{
	HandlerRequest hr(_br);
	hr.handle(_client);
	// for (client_vector::iterator it = _client.begin(); it != _client.end(); it++)
	// {
	// 	Request *	request	= &it->get_request();
	// 	Server &	server	= (*it).get_server();
	// 	// Response	response(*request, 200);

	// 	//Check if it was for closing , and also read the 
	// 	//incoming message 
	// 	hr
	// 		.set_client(it.base())
	// 		.set_request(&it->get_request())
	// 		.set_server(&it->get_server())
	// 	;
	// 	try{
	// 		hr.parse();
	// 		if (!hr.is_complete())
	// 			continue;
	// 		request->set_path(request->get_path() + server.get_index(request->get_path()));
	// 		if (server.get_cgi_map().find("." + Extension::get_extension(request->get_path())) != server.get_cgi_map().end())
	// 		{
	// 			// RequestCGI request_cgi(server.get_cgi_map()["." + Extension::get_extension(request->get_path())], );
	// 			// response.set_error(418);
	// 		}
	// 		else
	// 		{
	// 			if (server.is_directory(*request))
	// 				if (!server.get_auto_index())
	// 					response.set_error(403);
	// 				else
	// 				{
	// 					response
	// 						.set_code(200)
	// 						.set_body(server.get_index_page(*request))
	// 						.add_header("Content-type", "text/html");
	// 				}
	// 			else
	// 			{
	// 				request->set_path(server.get_full_path(request->get_path()));
	// 				// std::cout << "PATH : " << request->get_path() << std::endl;
	// 				request->action(response);
	// 			}
	// 		}
	// 	}
	// 	catch (BuilderRequest::BadRequest &e)
	// 	{
	// 		response.set_code(400).clear_header();
	// 	}
	// 	catch (BuilderRequest::BadHttpVersion &e)
	// 	{
	// 		response.set_code(505).clear_header();
	// 	}
	// 	catch (BuilderRequest::MethodNotImplemented &e)
	// 	{
	// 		response.set_code(501).clear_header();
	// 	}
	// 	catch (Request::NoMethod &e)
	// 	{
	// 		// std::cout << "test NoMethod" << std::endl;
	// 		std::cout << "Client " << it->get_socket() << " disconnected" << std::endl;  

	// 		close( it->get_socket() );  
	// 		_client.erase(it);  
	// 		break;
	// 	}
	// 	std::cout << "write in Socket: " << it->get_socket() << std::endl;
	// 	response.send_response(it->get_socket());

	// 	close( it->get_socket() );  
	// 	_client.erase(it);  
	// 	break;
	// }
}

void
Core::_detect_reset_server_poll_fd()
{
	if (!_client.size())
	{
		for (size_t i = 0; i < _servers.size(); i++)
		{
			Server & server = _servers[i];
			for (Server::port_map::iterator it = server.get_server_socket().begin(); 
					it != server.get_server_socket().end(); it++)
			{
				ServerSocket & server_socket = it->second;
				_fds[server_socket.get_id()].revents = 0;
			}
		}
	}
}
