/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:23:05 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/13 18:00:02 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void){}

Server::Server(std::string root, int port) : _root(root), _worker(3)
{
	addPort(port);
	_clientSockets.insert(_clientSockets.begin(), _worker, 0);
}

Server::Server(Server const & src)
{
	*this = src;
}

Server::~Server(void)
{
	
}

Server &	Server::operator=(Server const & rhs)
{
	if (&rhs != this)
		this->_name = rhs._name;
	return *this;
}


void	Server::addPort(int port)
{
	this->_serverSockets.push_back(ServerSocket(port));
}

void	Server::start()
{
	fd_set readfds;
	int c = sizeof(struct sockaddr_in);
	int maxfd = -1;
	int active = 0;
	int new_socket = -1;

	for (size_t i = 0; i < _serverSockets.size() ; i++)
	{
		_serverSockets[i].setupSocket();
		_serverSockets[i].bindSocket();
		_serverSockets[i].listenSocket(3);
	}
	while(true)
	{
		FD_ZERO(&readfds);
		FD_SET(_serverSockets[0].getSocket(), &readfds);
		maxfd = _serverSockets[0].getSocket();

		for (size_t i = 0; i < _clientSockets.size(); i++)
		{
			int fd = _clientSockets[i];
			if(fd > 0)
				FD_SET(fd, &readfds);
			if(fd > maxfd)
				maxfd = fd;
		}
		active = select( maxfd + 1, &readfds, NULL, NULL, NULL);
		if (FD_ISSET(_serverSockets[0].getSocket(), &readfds))
		{
			if ((new_socket = accept(_serverSockets[0].getSocket(), reinterpret_cast<sockaddr*>(&_serverSockets[0].getServer()) , reinterpret_cast<socklen_t*>(&c))) < 0)
			{
				perror("accept failed");
				exit(EXIT_FAILURE);
			}
			std::cout << "New connection, socket fd is " << new_socket << std::endl;
			for (int i = 0; i < _worker; i++)
			{  
				//if position is empty 
				if( _clientSockets[i] == 0 )  
				{  
					_clientSockets[i] = new_socket;  
					printf("Adding to list of sockets as %d\n" , i);  
						
					break;  
				}
			} 
		}
		for (int i = 0; i < _worker; i++)  
		{
			int fd = _clientSockets[i];  
			int valread;
			char buffer[1025];
					
			if (FD_ISSET( fd , &readfds))  
			{  
				//Check if it was for closing , and also read the 
				//incoming message 
				if ((valread = read( fd , buffer, 1024)) == 0)  
				{    
					std::cout << "Host disconnected" << std::endl;  

					close( fd );  
					_clientSockets[i] = 0;  
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