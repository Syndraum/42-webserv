/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:14:23 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/29 17:25:32 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerSocket.hpp"

ServerSocket::ServerSocket(int port) :
_port(port),
_ip(0),
_active(true)
{
	_socket = -1;
}

ServerSocket::ServerSocket(int port, uint32_t ip) :
_port(port),
_ip(ip),
_active(true)
{
	_socket = -1;
}

ServerSocket::ServerSocket(ServerSocket const & src)
{
	*this = src;
}

ServerSocket::~ServerSocket(void)
{
	
}

ServerSocket &
ServerSocket::operator=(ServerSocket const & rhs)
{
	if (&rhs != this){
		this->_port = rhs._port;
		this->_socket = rhs._socket;
		this->_address = rhs._address;
		this->_ip = rhs._ip;
		this->_active = rhs._active;
	}
	return *this;
}

void
ServerSocket::setup_socket()
{
	int one = 1;

	_socket = socket(AF_INET , SOCK_STREAM | SOCK_NONBLOCK , 0);
	if (_socket == -1)
		throw "Socket error";
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	_address.sin_port = htons( _port );
	setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &one, sizeof(int));
}

void
ServerSocket::bind_socket()
{
	if ((bind(_socket, reinterpret_cast<sockaddr*>(&_address), sizeof(_address)) < 0)){
		std::cerr << strerror(errno) << std::endl;
		throw std::exception();
	}
	std::cout << "bind done. Listen on port " << _port <<std::endl;
}

void
ServerSocket::listen_socket(int worker_connection)
{
	if ((listen(_socket, worker_connection)) < 0)
		throw "listen failed";
	std::cout << "Waiting for incoming connection..." << std::endl;
}

ServerSocket *
ServerSocket::set_port(int port)
{
	_port = port;
	return this;
}

int
ServerSocket::get_port() const
{
	return (_port);
}

ServerSocket *
ServerSocket::set_active(bool active)
{
	_active = active;
	return this;
}

bool
ServerSocket::get_active() const
{
	return (_active);
}

void
ServerSocket::print() const
{
	std::cout << " adress : " << this << "\n";
	std::cout << " port : " << _port << "\n";
	std::cout << " ip : " << _ip << "\n";
	std::cout << " active : " << std::boolalpha << _active << "\n";
	std::cout << " fd : " << _socket << "\n";
}
