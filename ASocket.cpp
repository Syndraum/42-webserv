/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:50:07 by cdai              #+#    #+#             */
/*   Updated: 2021/06/25 17:55:20 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASocket.hpp"

//ASocket::ASocket(void): _socket(0)
//{}
//
//ASocket::ASocket(int socket): _socket(socket)
//{}

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
	static char buffer[1024];
	std::string line;


//	buffer = new char[1024];
//	int ret = recv(_socket, buffer, 1023, 0);
	int ret = read(_socket, buffer, 1023);
	buffer[ret] = 0;
	line = buffer;
//	size_t found = line.find("\r\n");
	size_t found = line.find("\n");
	line.copy(buffer, ret - found, found);

	std::cout << "buffer: " << buffer << std::endl;

	str = line.substr(0, found);
	return 0;
}
