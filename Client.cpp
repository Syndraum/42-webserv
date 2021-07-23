#include "Client.hpp"

Client::Client(Server & server) : _server(server) {}

Client::Client(Client const & src) : _server(src._server)
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
		_request = rhs._request;
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

ClientSocket &
Client::get_socket_stuct()
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
	return (_server);
}
