/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:23:05 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/01 15:33:42 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void) :
_name("_"),
_auto_index(false),
_client_max_body_size(5)
{}

Server::Server(Server const & src)
{
	*this = src;
}

Server::~Server(void) {}

Server &
Server::operator=(Server const & rhs)
{
	if (&rhs != this){
		this->_name = rhs._name;
		this->_root = rhs._root;
		this->_server_sockets = rhs._server_sockets;
	}
	return *this;
}

Server &
Server::add_port(int port)
{
	this->_server_sockets.insert(std::pair<int, ServerSocket>(port, ServerSocket(port)));
	return(*this);
}

void
Server::start(int worker)
{
	for (port_vector::iterator it = _server_sockets.begin(); it != _server_sockets.end() ; it++)
	{
		ServerSocket & ss = it->second;

		ss.setup_socket();
		ss.bind_socket();
		ss.listen_socket(worker);
	}
}

Server::port_vector &
Server::get_server_socket(void)
{
	return (_server_sockets);
}

ServerSocket const &
Server::get_server_socket(int port) const
{
	return _server_sockets.at(port);
}

const bool &
Server::get_auto_index() const
{
	return (_auto_index);
}

Server &
Server::set_name(std::string name)
{
	_name = name;
	return(*this);
}

Server &
Server::set_root(std::string root)
{
	_root = root;
	return(*this);
}

Server &
Server::set_auto_index(bool auto_index)
{
	_auto_index = auto_index;
	return(*this);
}

Server &
Server::set_client_max_body_size(size_t limit)
{
	_client_max_body_size = limit;
	return(*this);
}

Server &
Server::set_path_error_page(std::string path)
{
	_path_error_page = path;
	return(*this);
}

void
Server::print() const
{
	std::cout << "Server " << _name << std::endl;
	std::cout << "adress " << this << std::endl;
	std::cout << "autoindex " << std::boolalpha << _auto_index << std::endl;
	for (port_vector::const_iterator it = _server_sockets.begin(); it != _server_sockets.end(); it++)
	{
		it->second.print();
	}
	if (_server_sockets.size() == 0)
		std::cout << "no port found\n";
}
