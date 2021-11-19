/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:34:02 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 01:03:23 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(Server & server, ServerSocket & server_socket) :
_request(),
_server(&server), 
_server_socket(&server_socket),
_strategy(0),
_response(0),
_state(READ_HEADER),
_revent(0),
_close(false)
{}

Client::Client(Client const & src) :
_server(src._server),
_server_socket(src._server_socket),
_strategy(0),
_response(0)
{
	*this = src;
}

Client::~Client(void)
{
	clean_reponse();
}

Client &
Client::operator=(Client const & rhs)
{
	clean_reponse();
	if (this != &rhs)
	{
		_request = rhs._request;
		_server = rhs._server;
		_socket = rhs._socket;
		_server_socket = rhs._server_socket;
		if (rhs._strategy)
			_strategy = rhs._strategy->clone();
		if (rhs._response)
			_response = new Response(*(rhs._response));
		_state = rhs._state;
		_revent = rhs._revent;
		_close = rhs._close;
	}
	return *this;
}

Request &
Client::get_request()
{
	return (_request);
}

const Request &
Client::get_request() const
{
	return (_request);
}

ClientSocket &
Client::get_socket_struct()
{
	return (_socket);
}

int
Client::get_socket()
{
	return (_socket.get_socket());
}

Server &
Client::get_server()
{
	return (*_server);
}

Server const &
Client::get_server() const
{
	return (*_server);
}

ServerSocket &
Client::get_server_socket()
{
	return (*_server_socket);
}

Response *
Client::get_response()
{
	return (_response);
}

std::string
Client::get_full_path() const
{
	const URI & uri = _request.get_uri();

	return (_server->get_full_path(uri.get_path()));
}

Client::request_state
Client::get_state() const
{
	return (_state);
}

short
Client::get_revent() const
{
	return (_revent);
}

void			
Client::set_state(request_state state)
{
	_state = state;
}

void
Client::set_revent(short revent)
{
	_revent = revent;
}

void
Client::set_server(Server * server)
{
	_server = server;
}

bool
Client::get_close() const
{
	return(_close);
}

void
Client::set_close(bool close)
{
	_close = close;
}

void
Client::set_server_socket(ServerSocket * server_socket)
{
	_server_socket = server_socket;
}

void
Client::set_strategy(IResponseStrategy * strategy)
{
	_strategy = strategy;
	_state = STRATEGY;
}

void
Client::do_strategy(Client & client)
{
	_response = _strategy->create(client);
	if (_strategy->is_finish()) {
		_state = SEND_RESPONSE;
	}
}

void
Client::send(int fd)
{
	try
	{
		if (_response == 0)
			throw std::exception();
		switch (_response->get_state())
		{
		case Response::WRITE_HEADER:
			if ((get_revent() & POLLOUT) != 0)
				_response->send_header(fd);
			break;
		case Response::WRITE_BODY:
			if ((get_revent() & POLLOUT) != 0)
				_response->send_body(fd);
			break;
		case Response::END:
			_state = Client::END;
			break;
		default:
			break;
		}
	}
	catch (std::exception& e)
	{
		try
		{
			ExitException	&e_exit = dynamic_cast<ExitException&>(e);
			(void)e_exit;
			throw (ExitException());
		}
		catch (std::bad_cast &bc)
		{
			_state = Client::END;
		}
	}
}

void
Client::clean_reponse()
{
	delete _response;
	_response = 0;
	delete _strategy;
	_strategy = 0;
}