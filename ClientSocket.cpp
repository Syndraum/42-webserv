/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:14:07 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/14 18:19:23 by cdai             ###   ########.fr       */
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
	ASocket::operator=(rhs);
	_request = rhs._request;
	_server = rhs._server;
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
