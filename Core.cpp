/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:51 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/17 18:14:12 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"

Core::Core(void) : _worker(3), _maxfd(-1), _nbActive(0)
{
}

Core::Core(Core const & src)
{
	*this = src;
}

Core::~Core(void)
{
	
}

Core &	Core::operator=(Core const & rhs)
{
	if (&rhs != this)
		this->_worker = rhs._worker;
	return *this;
}

void	Core::start(){
	int new_socket = -1;
	int c = sizeof(struct sockaddr_in);
	int fd;
	std::vector<int> activeSocket;

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
	// int main_fd = _servers[0].getServerSocket(8080).getSocket();
	while (true)
	{
		FD_ZERO(&_readfds);
		for (size_t i = 0; i < _serverSockets.size(); i++)
		{
			fd = _serverSockets[i];
			FD_SET(fd, &_readfds);
			if(fd > _maxfd)
				_maxfd = fd;
		}
		for (size_t i = 0; i < _client.size(); i++)
		{
			int fd = _client[i].getSocket();
			if(fd > 0)
				FD_SET(fd, &_readfds);
			if(fd > _maxfd)
				_maxfd = fd;
		}
		_nbActive = select( _maxfd + 1, &_readfds, NULL, NULL, NULL);
		for (size_t i = 0; i < _serverSockets.size(); i++)
		{
			int fd = _serverSockets[i];

			if (FD_ISSET(fd, &_readfds))
			{
				_client.push_back(ClientSocket());
				ClientSocket & cs = _client.back();
				if ((new_socket = accept(fd, &cs.getAddress() , reinterpret_cast<socklen_t*>(&c))) < 0)
				{
					perror("accept failed");
					exit(EXIT_FAILURE);
				}
				std::cout << "New connection, socket fd is " << new_socket << ", socket server :" << fd << std::endl;
				cs.setSocket(new_socket);
				std::cout << "Adding to list of sockets as " << _client.size() << std::endl;
				// printf("Adding to list of sockets as %zu\n" , _client.size());
			}
		}
		for (client_vector::iterator it = _client.begin(); it != _client.end(); it++)
		{
			int fd = it->getSocket();  
			int valread;
			char buffer[1025];

			if (FD_ISSET( fd , &_readfds)) 
			{
				//Check if it was for closing , and also read the 
				//incoming message 
				if ((valread = read( fd , buffer, 1024)) == 0)  
				{    
					std::cout << "Host disconnected" << std::endl;  

					close( fd );  
					_client.erase(it);  
					break;
				}  
						
				//Echo back the message that came in 
				else 
				{  
					//set the string terminating NULL byte on the end 
					//of the data read 
					buffer[valread] = '\0';  
					send(fd , buffer , std::strlen(buffer) , 0 );  
				} 
			}
		}
	}
}

void	Core::addServer(Server & server)
{
	_servers.push_back(server);
}

void	Core::addServer()
{
	_servers.push_back(Server(""));
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
