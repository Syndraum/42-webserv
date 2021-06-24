/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:51 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/23 15:22:33 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"
#include <cstring>
#include <fstream>

Core::Core(void) :
	_worker(3),
	//_maxfd(-1),
	_nbActive(0)
{
}

Core::Core(Core const & src)
{
	*this = src;
}

Core::~Core(void)
{}

Core &	Core::operator=(Core const & rhs)
{
	if (&rhs != this)
		this->_worker = rhs._worker;
	return *this;
}

void	Core::start(){
	int fd;
	std::vector<int> activeSocket;

	_fds = new struct pollfd[10];

	for (size_t i = 0; i < _servers.size(); i++)
	{
		_servers[i].start(_worker);
		activeSocket = _servers[i].getActiveSocket();
		_serverSockets.insert(
			_serverSockets.begin(),
			activeSocket.begin(),
			activeSocket.end()
		);
	}
	while (true)
	{
		// value given to poll (nbFds)
		_nbFds = 0;
		for (size_t i = 0; i < _serverSockets.size(); i++)
		{
			fd = _serverSockets[i];
			_fds[_nbFds].fd = fd;
			_fds[_nbFds].events = POLLIN;
			_fds[_nbFds].revents = 0;
			_nbFds++;
		}
		for (size_t i = 0; i < _client.size(); i++)
		{
			fd = _client[i].getSocket();
			_fds[_nbFds].fd = fd;
			_fds[_nbFds].events = POLLOUT;
			_fds[_nbFds].revents = 0;
			_nbFds++;
		}
		_nbActive = poll(_fds, _nbFds, 60000);
		_acceptConnection();
		_detectCloseConnection();
		_detectResetServerPollFD();

		// detect and set serversocket to POLLIN or not
		_detectResetServerPollFD();
	}
}

void	Core::addServer(Server & server)
{
	_servers.push_back(server);
}

Server	&	Core::addServer()
{
	_servers.push_back(Server());
	return(_servers.back());
}

Server	&	Core::getServer(int index)
{
	return (_servers.at(index));
}

void	Core::print()
{
	for (size_t i = 0; i < _servers.size(); i++)
	{
		_servers[i].print();
	}
	if (_servers.size() == 0)
		std::cout << "no Server found \n";
}

void	Core::_acceptConnection()
{
	int new_socket = -1;
	int one = 1;

	for (size_t i = 0; i < _serverSockets.size(); i++)
	{
		int fd = _serverSockets[i];

		if (_fds[i].revents & POLLIN)
		{
			_client.push_back(ClientSocket());
			ClientSocket & cs = _client.back();
			if ((new_socket = accept(fd, &cs.getAddress() , reinterpret_cast<socklen_t*>(&_SIZE_SOCK_ADDR))) < 0)
			{
				perror("accept failed");
				exit(EXIT_FAILURE);
			}
			setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
			std::cout << "New connection, socket fd is " << new_socket << ", socket server :" << fd << std::endl;
			cs.setSocket(new_socket);
			std::cout << "Adding to list of sockets as " << _client.size() << std::endl;
		}
	}
}

// this function is more 'read' than 'close'
void	Core::_detectCloseConnection()
{
	for (client_vector::iterator it = _client.begin(); it != _client.end(); it++)
	{
		int fd = it->getSocket();  
		int valread;
		char buffer[1025];
		int fds_index;

		for (unsigned long i = 0; i < _serverSockets.size(); i++)
			if (fd == _fds[i].fd)
				fds_index = i;
		//Check if it was for closing , and also read the 
		//incoming message 
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
			buffer[valread] = '\0';

			std::cout << buffer << std::endl;


			// TODO !! to update with Request Class
			std::string ROOT = ".";
			std::string request(buffer);
			std::string requested_file = _cdai_temp_get_requested_file(request);
			std::string filename = ROOT + requested_file;
			if (filename == "./")
				filename = "./index.html";

			// create and send response
			Response response(200);
			response.setBody(filename);

			// need client socket
			ClientSocket & cs = _client.back();
			int clientSocket = cs.getSocket();

			response.sendResponse(clientSocket);




			std::cout << "Host disconnected" << std::endl;  // message for debug, to remove later

			close( fd );  
			_client.erase(it);  
			break;
		}
	}
}

void	Core::_detectResetServerPollFD()
{
	if (!_client.size())
		for (size_t i = 0; i < _serverSockets.size(); i++)
			if (_fds[i].revents & POLLIN)
			{
				_fds[i].revents = 0;
				std::cout << "revents = 0 (to remove from Core.cpp - line 206)" << std::endl;
			}
}

std::string Core::_cdai_temp_get_requested_file(std::string & buffer)
{
	std::size_t start = buffer.find('/');
	std::size_t end = buffer.find(' ', start + 1);

	return buffer.substr(start, end - start);
}
