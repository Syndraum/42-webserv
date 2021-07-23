/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReaderSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:45:01 by cdai              #+#    #+#             */
/*   Updated: 2021/07/23 12:05:05 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReaderSocket.hpp"

ReaderSocket::ReaderSocket(int fd):
_fd(fd)
{}

ReaderSocket::ReaderSocket(ReaderSocket const & rhs)
{
	*this = rhs;
}

ReaderSocket::~ReaderSocket(void)
{}

ReaderSocket const & ReaderSocket::operator=(ReaderSocket const & rhs)
{
	return (*this);
}

int ReaderSocket::get_next_line(std::string & line)
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

	return (response);
}

void
ReaderSocket::read_body(std::string & line, int content_length)
{
	line = _buffer;
	_buffer[0] = 0;
	char buffer[content_length + 1];
	int ret = recv(_socket, buffer, content_length, MSG_DONTWAIT);
	buffer[ret] = 0;
	line = line + buffer;
//	std::cout << "body: " << line << std::endl;
}

void
ReaderSocket::read_until_end(void)
{
	std::string temp;
	get_next_line(temp);

//	std::cout << "temp: " << temp << std::endl;
}
