#include "Client.hpp"

Client::Client(Server & server, ServerSocket & server_socket) :
_server(server), 
_server_socket(server_socket)
{}

Client::Client(Client const & src) :
_server(src._server),
_server_socket(src._server_socket)
{
	*this = src;
}

Client::~Client(void)
{
	
}

Client &
Client::operator=(Client const & rhs)
{
	if (this != &rhs)
	{
		_request = rhs._request;
		_server = rhs._server;
		_socket = rhs._socket;
		_server_socket = rhs._server_socket;
	}
	return *this;
}

Request &
Client::get_request()
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
	return (_server);
}

ServerSocket &
Client::get_server_socket()
{
	return (_server_socket);
}

std::string
Client::get_full_path() const
{
	const URI & uri = _request.get_uri();

	return (_server.get_full_path(uri.get_path()));
}

void
Client::set_server(Server & server)
{
	_server = server;
}

void
Client::set_server_socket(ServerSocket & server_socket)
{
	_server_socket = server_socket;
}