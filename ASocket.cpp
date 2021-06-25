/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:50:07 by cdai              #+#    #+#             */
/*   Updated: 2021/06/25 18:15:46 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.hpp"

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

int		ASocket::get_next_line(std::string & str)
{
	static char buffer[1024] = {0};
	std::string line;
	int ret = 0;

	if (!buffer[0])
	{
//	ret = recv(_socket, buffer, 1023, 0);
	ret = read(_socket, buffer, 1023);
	buffer[ret] = 0;
	}
	line = buffer;
//	size_t found = line.find("\r\n");
	size_t found = line.find("\n");
	line.copy(buffer, ret - found, found + 1);
	buffer[ret - found - 1] = 0;

//	std::cout << "buffer: " << buffer << std::endl;

	str = line.substr(0, found);
	return 0;
}
