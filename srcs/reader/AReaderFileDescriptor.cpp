/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AReaderFileDescriptor.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:22:22 by cdai              #+#    #+#             */
/*   Updated: 2021/07/26 13:38:06 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AReaderFileDescriptor.hpp"

AReaderFileDescriptor::AReaderFileDescriptor(void)
{}

AReaderFileDescriptor::AReaderFileDescriptor(int fd):
_fd(fd)
{
	_reset_buffer();
}

AReaderFileDescriptor::AReaderFileDescriptor(AReaderFileDescriptor const & rhs)
{
	*this = rhs;
}

AReaderFileDescriptor::~AReaderFileDescriptor(void)
{}

AReaderFileDescriptor const &
AReaderFileDescriptor::operator=(AReaderFileDescriptor const & rhs)
{
	_fd = rhs._fd;
	for (int i = 0; i < BUFFER_SIZE; i++)
		_buffer[i] = rhs._buffer[i];
	return *this;
}

void
AReaderFileDescriptor::_reset_buffer(void)
{
	for (int i = 0; i < BUFFER_SIZE; i++)
		_buffer[i] = '\0';
}

int
AReaderFileDescriptor::get_fd(void)
{
	return (_fd);
}

void
AReaderFileDescriptor::set_fd(int fd)
{
	_fd = fd;
}

int AReaderFileDescriptor::get_next_line(std::string & line)
{
	int	response = 2;
	int ret = 1;

	std::string temp("");
	size_t found;
	line = "";

	while (response > 1)
	{
		temp += _buffer;
		found = temp.find("\r\n");
		// std::cout << "temp: " << temp << std::endl;
//		std::cout << "found: " << found << std::endl;

		if (ret == 0) //cdai, if the client close his socket, it send EOF
		{
			line = temp;
			response = 0;
		}
		else if (found == std::string::npos) //cdai, if i don't find "\r\n", i call recv
		{
//			std::cout << "recv" << std::endl;
//			std::cout << "ASocket->_socket" << _socket << std::endl;
			//ret = recv(_fd, _buffer, BUFFER_SIZE - 1, MSG_DONTWAIT);
			ret = _read();
//			std::cout << "ret: " << ret << std::endl;

			// we cannot use ERRNO, so we don't know which kind of error it is
			// if the socket is empty (when we already read EOF), recv send always -1
			if (ret == -1) // handle segfault on index -1. Mainly, it will send -1 while the socket is open and there is nothing to read
				return -1;
			_buffer[ret] = 0;
		}
		else //we found "\r\n" then we call substr
		{
			// strdup ou substr
			line = temp.substr(0, found);
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
AReaderFileDescriptor::read_body(std::string & line, int content_length)
{
	line = _buffer;
	_buffer[0] = 0;
	char buffer[content_length + 1];
	int ret = recv(_fd, buffer, content_length, MSG_DONTWAIT);
	buffer[ret] = 0;
	line = line + buffer;
	std::cout << "body: " << line << std::endl;
}

void
AReaderFileDescriptor::read_until_end(std::string & line)
{
	get_next_line(line);

//	std::cout << "temp: " << temp << std::endl;
}
