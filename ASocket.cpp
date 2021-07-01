/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:50:07 by cdai              #+#    #+#             */
/*   Updated: 2021/07/01 16:56:38 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.hpp"

ASocket::ASocket(void)
{
	reset_buffer();
}

ASocket::~ASocket(void)
{}

int	ASocket::get_socket(void) const
{
	return _socket;
}

void	ASocket::set_socket(int socket)
{
	_socket = socket;
}

sockaddr_in	& ASocket::get_address(void)
{
	return this->_address;
}

void		ASocket::set_address(sockaddr_in & Address)
{
	this->_address = Address;
}

int		ASocket::get_next_line(std::string & str)
{
	int	response = 2;
	int ret = 1;
//	static char buffer[BUFFER_SIZE];

	std::string temp("");
	size_t found;
	str = "";

	while (response > 1)
	{
		temp += _buffer;
		found = temp.find("\r\n");
//		std::cout << "temp: " << temp << std::endl;
//		std::cout << "found: " << found << std::endl;
		if (ret == 0)
		{
			str = temp;
			response = 0;
		}
		else if (found == std::string::npos)
		{
//			std::cout << "recv" << std::endl;
			ret = recv(_socket, _buffer, BUFFER_SIZE - 1, MSG_DONTWAIT);
			std::cout << "ret" << ret << std::endl;
//			if (ret == 0)
//				return 0;
			if (ret == -1)
				return -1;
			_buffer[ret] = 0;
		}
		else
		{
			// strdup ou substr
			str = temp.substr(0, found);
			response = 1;
		}
	}


	if (temp.length() > found)
	{
		temp.copy(_buffer, temp.length() - found - 2, found + 2);
		_buffer[temp.length() - found - 2] = 0;
	}

	return response;
}

void	ASocket::reset_buffer(void)
{
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		_buffer[i] = '\0';
	}
}
