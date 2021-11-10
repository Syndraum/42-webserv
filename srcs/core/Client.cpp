#include "Client.hpp"

Client::Client(Server & server, ServerSocket & server_socket) :
_server(&server), 
_server_socket(&server_socket),
_strategy(0),
_response(0),
_state(READ_HEADER)
{}

Client::Client(Client const & src) :
_server(src._server),
_server_socket(src._server_socket)
{
	*this = src;
}

Client::~Client(void)
{
	// clean_reponse();
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
		_strategy = rhs._strategy;
		_response = rhs._response;
		_state = rhs._state;
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

void
Client::set_server(Server * server)
{
	_server = server;
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
	_state = SEND_RESPONSE;
}

void
Client::send(int fd)
{
	if (_response == 0)
		throw std::exception();
	_response->send(fd);
}

void
Client::clean_reponse()
{
	delete _response;
	_response = 0;
	delete _strategy;
	_strategy = 0;
}