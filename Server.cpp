/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:23:05 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/17 18:20:18 by syndraum         ###   ########.fr       */
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
	if (&rhs != this){
		this->_name = rhs._name;
		this->_root = rhs._root;
		this->_serverSockets = rhs._serverSockets;
	}
	return *this;
}


Server &	Server::addPort(int port)
{
	this->_serverSockets.insert(std::pair<int, ServerSocket>(port, ServerSocket(port)));
	return(*this);
}

void	Server::start(int worker)
{
	for (port_vector::iterator it = _serverSockets.begin(); it != _serverSockets.end() ; it++)
	{
		ServerSocket & ss = it->second;

		ss.setupSocket();
		ss.bindSocket();
		ss.listenSocket(worker);
		_activePort.push_back(ss.getPort());
		_activeSocket.push_back(ss.getSocket());
	}
}

ServerSocket	& Server::getServerSocket(int port)
{
	return _serverSockets.at(port);
}

std::vector<int> &	Server::getActiveSocket()
{
	return _activeSocket;
}

void	Server::print()
{
	std::cout << "Server " << _name << std::endl;
	for (port_vector::iterator it = _serverSockets.begin(); it != _serverSockets.end(); it++)
	{
		it->second.print();
	}
	if (_serverSockets.size() == 0)
		std::cout << "no port found\n";
	
}