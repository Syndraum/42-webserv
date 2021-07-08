/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:14:07 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/01 15:21:21 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientSocket.hpp"

// ClientSocket::ClientSocket(void) : ASocket(), _request()
// {
// 	// _address = {0};
// 	_socket = 0;
// }

ClientSocket::ClientSocket(Server & server) : ASocket(), _request(), _server(server)
{
	// _address = {0};
	_socket = 0;
}

ClientSocket::ClientSocket(ClientSocket const & src) : _server(src._server)
{
	*this = src;
}

ClientSocket::~ClientSocket(void) {}

ClientSocket &
ClientSocket::operator=(ClientSocket const & rhs)
{
	if (&rhs != this)
		this->_socket = rhs._socket;
	return *this;
}

Request &
ClientSocket::get_request()
{
	return (_request);
}

Server &
ClientSocket::get_server()
{
	return (_server);
}