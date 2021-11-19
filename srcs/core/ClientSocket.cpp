/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:14:07 by syndraum          #+#    #+#             */
/*   Updated: 2021/11/19 21:18:00 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

ClientSocket::ClientSocket(void) : ASocket()
{}


ClientSocket::ClientSocket(ClientSocket const & src)
{
	*this = src;
}

ClientSocket::~ClientSocket(void) {}

ClientSocket &
ClientSocket::operator=(ClientSocket const & rhs)
{
	ASocket::operator=(rhs);
	return *this;
}

std::string
ClientSocket::get_ip()
{
	std::stringstream ss;
	size_t	ip		= _address.sin_addr.s_addr;
	size_t	byte	= 0;

	for (size_t i = 0; i < 4; i++)
	{
		byte = ip % 256;
		ss << byte;
		if (i != 3)
		{
			ss << ".";
			ip >>= 8;
		}
	}
	return (ss.str());
}
