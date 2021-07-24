/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:50:07 by cdai              #+#    #+#             */
/*   Updated: 2021/07/14 18:06:23 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.hpp"

ASocket::ASocket(void) : _id(-1)
{
	reset_buffer();
}

ASocket::ASocket(ASocket const & rhs)
{
	*this = rhs;
}

ASocket::~ASocket(void)
{}

ASocket const & ASocket::operator=(ASocket const & rhs)
{
	_socket = rhs._socket;
	_address = rhs._address;
	for (int i = 0; i < BUFFER_SIZE; i++)
		_buffer[i] = rhs._buffer[i];
	return *this;
}

int
ASocket::get_socket(void) const
{
	return _socket;
}

void
ASocket::set_socket(int socket)
{
	_socket = socket;
}

const sockaddr_in &
ASocket::get_address(void) const
{
	return _address;
}

void
ASocket::set_address(const sockaddr_in & Address)
{
	this->_address = Address;
}

int
ASocket::get_id() const
{ return (_id); }


void
ASocket::set_id(int id)
{ _id = id; }

int
ASocket::get_next_line(std::string & str)
{
	int	response = 2;
	int ret = 1;

	std::string temp("");
	size_t found;
	str = "";

	while (response > 1)
	{
		temp += _buffer;
		found = temp.find("\r\n");
//		std::cout << "temp: " << temp << std::endl;
//		std::cout << "found: " << found << std::endl;

		if (ret == 0) //cdai, if the client close his socket, it send EOF
		{
			str = temp;
			response = 0;
		}
		else if (found == std::string::npos) //cdai, if i don't find "\r\n", i call recv
		{
//			std::cout << "recv" << std::endl;
//			std::cout << "ASocket->_socket" << _socket << std::endl;
			ret = recv(_socket, _buffer, BUFFER_SIZE - 1, MSG_DONTWAIT);
//			std::cout << "ret" << ret << std::endl;

			// we cannot use ERRNO, so we don't know which kind of error it is
			// if the socket is empty (when we already read EOF), recv send always -1
			if (ret == -1) // handle segfault on index -1. Mainly, it will send -1 while the socket is open and there is nothing to read
				return -1;
			_buffer[ret] = 0;
		}
		else //we found "\r\n" then we call substr
		{
			// strdup ou substr
			str = temp.substr(0, found);
			response = 1;
		}
	}

	if (temp.length() > found) //Handle found == std::string::npos (size_t MAX)
	{
		temp.copy(_buffer, temp.length() - found - 2, found + 2);
		_buffer[temp.length() - found - 2] = 0;
	}

	return response;
}

void
ASocket::reset_buffer(void)
{
	for (int i = 0; i < BUFFER_SIZE; i++)
		_buffer[i] = '\0';
}
