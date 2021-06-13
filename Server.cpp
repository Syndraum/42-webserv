/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:23:05 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/13 16:19:55 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void){}

Server::Server(std::string root, int port) : _root(root)
{
	addPort(port);
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
	int c = sizeof(struct sockaddr_in);

	for (size_t i = 0; i < _serverSockets.size() ; i++)
	{
		_serverSockets[i].SetupSocket();
		_serverSockets[i].bindSocket();
		_serverSockets[i].listenSocket(3);
	}
	while( (_clientSocket = accept(_serverSockets[0].GetSocket(), reinterpret_cast<sockaddr*>(&_serverSockets[0].GetServer()) , reinterpret_cast<socklen_t*>(&c))))
	{
		puts("Connection accepted");
	}
	if (_clientSocket < 0)
		perror("accept failed");
}