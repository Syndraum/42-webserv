#include "ServerSocket.hpp"

ServerSocket::ServerSocket(int port) : _port(port), _socket(-1)
{}

ServerSocket::ServerSocket(ServerSocket const & src)
{
	*this = src;
}

ServerSocket::~ServerSocket(void)
{
	
}

ServerSocket &	ServerSocket::operator=(ServerSocket const & rhs)
{
	if (&rhs != this)
		this->_port = rhs._port;
	return *this;
}

void			ServerSocket::SetupSocket()
{
	_socket = socket(AF_INET , SOCK_STREAM , 0);
	if (_socket == -1)
		throw "Socket error";

	_server.sin_family = AF_INET;
	_server.sin_addr.s_addr = INADDR_ANY;
	_server.sin_port = htons( _port );
}

void			ServerSocket::bindSocket()
{
	if ((bind(_socket, reinterpret_cast<sockaddr*>(&_server), sizeof(_server)) < 0))
		throw "Bind failed";
	std::cout << "bind done" << std::endl;
}

void			ServerSocket::listenSocket(int worker_connection)
{
	if ((listen(_socket, worker_connection)) < 0)
		throw "listen failed";
	std::cout << "Waiting for incoming connection..." << std::endl;
}

ServerSocket *	ServerSocket::SetPort(int port)
{
	_port = port;
	return this;
}

int				ServerSocket::GetPort()
{
	return (_port);
}

int				ServerSocket::GetSocket()
{
	return (_socket);
}

sockaddr_in &		ServerSocket::GetServer()
{
	return (_server);
}
