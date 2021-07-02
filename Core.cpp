/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:51 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/02 15:58:24 by cdai             ###   ########.fr       */
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
		active_socket = _servers[i].get_active_socket();
		_server_sockets.insert(
			_server_sockets.begin(),
			active_socket.begin(),
			active_socket.end()
		);
	}
	while (true)
	{

		// value given to poll (nbFds)
		_nb_fds = 0;
		for (size_t i = 0; i < _server_sockets.size(); i++)
		{
			fd = _server_sockets[i];
			_fds[_nb_fds].fd = fd;
			_fds[_nb_fds].events = POLLIN;
			_fds[_nb_fds].revents = 0;
			_nb_fds++;
		}
		for (size_t i = 0; i < _client.size(); i++)
		{
			fd = _client[i].get_socket();
			_fds[_nb_fds].fd = fd;
			_fds[_nb_fds].events = POLLOUT;
			_fds[_nb_fds].revents = 0;
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

	for (size_t i = 0; i < _server_sockets.size(); i++)
	{
		int fd = _server_sockets[i];

		if (_fds[i].revents == _fds[i].events)
		{
			_client.push_back(ClientSocket());
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

void
Core::_handle_request_and_detect_close_connection()
{
	for (client_vector::iterator it = _client.begin(); it != _client.end(); it++)
	{
//		std::cout << "test" << std::endl;

		// BuilderRequest	br(_methods);
		Request * request = &it->get_request();
		Response response(200);
//		std::cout << "test" << std::endl;

		//Check if it was for closing , and also read the 
		//incoming message 
		try{
			_br.set_request(request);
			_br.parse_request(*it);
			// request = br.get_request();
			// br.reset();
//			std::cout << "path : " << request->get_path() << std::endl;
//			std::cout << "request : " << request->get_method()->get_name() << std::endl;
			if (request->get_path() == "/")
				request->set_path("/index.html");
			request->set_path("./webserviette_root" + request->get_path());
			request->set_version("HTTP/1.1");

			request->action(response);
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
			continue;
		}
		catch (Request::NoMethod &e)
		{
//			std::cout << "Client " << it->get_socket() << " disconnected" << std::endl;  

//			close( it->get_socket() );  
//			_client.erase(it);  
			break;
		}
		// std::cout << "parse_request: " <<  parse_ret << std::endl;

		// std::cout << "method: " << request.get_method() << std::endl;

		//if (parse_ret == OK)
		//{
			// std::string ROOT = "./webserviette_root";
			// std::string filename = ROOT + request.get_path();

		// delete request;
		request->reset();
		std::cout << "write in Socket: " << it->get_socket() << std::endl;
		response.send_response(it->get_socket());

		close( it->get_socket() );  
		_client.erase(it);  
		break;
		//}
	}
}

void
Core::_detect_reset_server_poll_fd()
{
	if (!_client.size())
		for (size_t i = 0; i < _server_sockets.size(); i++)
			if (_fds[i].revents & POLLOUT || _fds[i].revents & POLLIN)
				_fds[i].revents = 0;
}

void	Core::_cdai_dirty_function()
{
	for (client_vector::iterator it = _client.begin(); it != _client.end(); it++)
	{
//		std::cout << "test" << std::endl;

		int valread;
		char buffer[1025];
		Request request;
		int fd = it->get_socket();

		if ((valread = recv( fd , buffer, 1024, MSG_DONTWAIT)) == 0)  
		//if ((valread = recv( fd , buffer, 1024, 0)) == 0)  
		{
			std::cout << "Host disconnected" << std::endl;  

			close( fd );  
			_client.erase(it);  
			break;
		}

		else if(valread > 0)
		{

			// debug
			buffer[valread] = '\0';
			std::cout << buffer << std::endl;

			// parse_request ?
//			std::stringstream ss;
//			ss << buffer;
//			parse_request(ss, &request);

			// get requested file path
			std::string ROOT = "./webserviette_root";
			std::string filename = ROOT + _get_path(buffer);

			std::cout << filename << std::endl;
			if (filename == ROOT + "/")
				filename += "index.html";

			// create and send response
			Response response(200);
			try
			{
				response.set_body(filename);
			}
			catch (std::exception & e)
			{
				std::cout << e.what() << std::endl;

				filename = ROOT + "/404.html";
				response.set_404(filename);
			}

			// need client socket
			ClientSocket & cs = _client.back();
			int clientSocket = cs.get_socket();

			std::cout << "clientSocket: " << clientSocket << std::endl;
			response.send_response(it->get_socket());

			// message for debug, to remove later
			std::cout << "Server still connected" << std::endl << std::endl;

			//close( fd );  
			//_client.erase(it);  
			break;
		}
	}

}

std::string Core::_get_path(std::string buffer)
{
	std::string path;
	size_t start = buffer.find("/");
	size_t end = buffer.find(" HTTP");

	path = buffer.substr(start, end - start);
	return path;
}
