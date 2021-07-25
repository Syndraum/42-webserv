/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:14:07 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/24 19:21:49 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

ClientSocket::ClientSocket(void) : ASocket()
{
}


ClientSocket::ClientSocket(ClientSocket const & src)
{
	*this = src;
}

ClientSocket::~ClientSocket(void) {}

ClientSocket &
ClientSocket::operator=(ClientSocket const & rhs)
{
	if (this != &rhs)
		ASocket::operator=(rhs);
	return *this;
}
