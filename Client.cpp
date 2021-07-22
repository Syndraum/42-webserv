#include "Client.hpp"

Client::Client(Server & server, ClientSocket & socket) : _server(server), _socket(socket) {}

Client::Client(Client const & src) : _server(src._server), _socket(src._socket)
{
	*this = src;
}

Client::~Client(void)
{
	
}

Client &
Client::operator=(Client const & rhs)
{
	if (this == &rhs)
	{
		_server = rhs._server;
		_socket = rhs._socket;
	}
	return *this;
}

Request &
Client::get_request()
{
	return (_request);
}

Server &
Client::get_server()
{
	return (_server);
}
