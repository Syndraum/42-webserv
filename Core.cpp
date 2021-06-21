/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:51 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/21 18:41:29 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"
#include <cstring>
#include <fstream>

Core::Core(void) :
	_worker(3),
	//_maxfd(-1),
	_nbActive(0)
{
}

Core::Core(Core const & src)
{
	*this = src;
}

Core::~Core(void)
{}

Core &	Core::operator=(Core const & rhs)
{
	if (&rhs != this)
		this->_worker = rhs._worker;
	return *this;
}

void	Core::start(){
	int fd;
	std::vector<int> activeSocket;

	_fds = new struct pollfd[10];

	for (size_t i = 0; i < _servers.size(); i++)
	{
		_servers[i].start(_worker);
		activeSocket = _servers[i].getActiveSocket();
		_serverSockets.insert(
			_serverSockets.begin(),
			activeSocket.begin(),
			activeSocket.end()
		);
	}
	while (true)
	{
		// value given to poll (nbFds)
		_nbFds = 0;
		for (size_t i = 0; i < _serverSockets.size(); i++)
		{
			fd = _serverSockets[i];
			_fds[_nbFds].fd = fd;
			_fds[_nbFds].events = POLLIN;
			_fds[_nbFds].revents = 0;
			_nbFds++;
		}
		for (size_t i = 0; i < _client.size(); i++)
		{
			fd = _client[i].getSocket();
			_fds[_nbFds].fd = fd;
			_fds[_nbFds].events = POLLOUT;
			_fds[_nbFds].revents = 0;
			_nbFds++;
		}
		_nbActive = poll(_fds, _nbFds, 60000);
		_acceptConnection();
		_detectCloseConnection();
		_detectResetServerPollFD();

		// detect and set serversocket to POLLIN or not
		_detectResetServerPollFD();
	}
}

void	Core::addServer(Server & server)
{
	_servers.push_back(server);
}

void	Core::addServer()
{
	_servers.push_back(Server(""));
}

Server	&	Core::getServer(int index)
{
	return (_servers.at(index));
}

void	Core::print()
{
	for (size_t i = 0; i < _servers.size(); i++)
	{
		_servers[i].print();
	}
	if (_servers.size() == 0)
		std::cout << "no Server found \n";
}

void	Core::_acceptConnection()
{
	int new_socket = -1;
	int one = 1;

	for (size_t i = 0; i < _serverSockets.size(); i++)
	{
		int fd = _serverSockets[i];

		if (_fds[i].revents & POLLIN)
		{
			_client.push_back(ClientSocket());
			ClientSocket & cs = _client.back();
			if ((new_socket = accept(fd, &cs.getAddress() , reinterpret_cast<socklen_t*>(&_SIZE_SOCK_ADDR))) < 0)
			{
				perror("accept failed");
				exit(EXIT_FAILURE);
			}
			setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
			std::cout << "New connection, socket fd is " << new_socket << ", socket server :" << fd << std::endl;
			cs.setSocket(new_socket);
			std::cout << "Adding to list of sockets as " << _client.size() << std::endl;
		}
	}
}

// this function is more 'read' than 'close'
void	Core::_detectCloseConnection()
{
	for (client_vector::iterator it = _client.begin(); it != _client.end(); it++)
	{
		int fd = it->getSocket();  
		int valread;
		char buffer[1025];
		int fds_index;

		for (unsigned long i = 0; i < _serverSockets.size(); i++)
			if (fd == _fds[i].fd)
				fds_index = i;
		//Check if it was for closing , and also read the 
		//incoming message 
		if ((valread = recv( fd , buffer, 1024, MSG_DONTWAIT)) == 0)  
		//if ((valread = recv( fd , buffer, 1024, 0)) == 0)  
		{
			std::cout << "Host disconnected" << std::endl;  

			close( fd );  
			_client.erase(it);  
			break;
		}

		else if(valread > 0)
		{
			buffer[valread] = '\0';
		
			std::cout << buffer << std::endl;

			if (strstr(buffer, "temp"))
				_cdaiTempSendImage();
			else if (strstr(buffer, "favicon"))
				_cdaiTempSendFavicon();
			else
				_cdaiTempSendResponse();

//			send(fd , buffer , std::strlen(buffer) , 0 );

			std::cout << "Host disconnected" << std::endl;  

			close( fd );  
			_client.erase(it);  
			break;
		}

		//Echo back the message that came in 
		//and echo in stdin/std::cout
//		else
//		{
//			//set the string terminating NULL byte on the end
//			//of the data read
//			buffer[valread] = '\0';
//			std::cout << buffer << std::endl;
//			send(fd , buffer , std::strlen(buffer) , 0 );
//		}
	}
}

void	Core::_detectResetServerPollFD()
{
	if (!_client.size())
		for (size_t i = 0; i < _serverSockets.size(); i++)
			if (_fds[i].revents & POLLIN)
			{
				_fds[i].revents = 0;
				std::cout << "revents = 0 (to remove from Core.cpp - line 174)" << std::endl;
			}
}

void	Core::_cdaiTempSendResponse()
{
	
	std::ifstream ifs("./index.html");

	ifs.seekg (0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg (0, ifs.beg);

	char * buffer = new char [length + 1];

    std::cout << "Reading " << length << " characters... ";
    // read data as a block:
    ifs.read (buffer,length);
	buffer[length + 1] = 0;

    if (ifs)
      std::cout << buffer << std::endl;
    else
      std::cout << "error: only " << ifs.gcount() << " could be read";
	
	ClientSocket & cs = _client.back();
	int clientSocket = cs.getSocket();

	char header[] =
		"HTTP/1.1 200 OK\r\n"
		"Content-Length: 369\r\n"
		"Content-Type: text/html; charset=UTF-8\r\n\r\n";

	send(clientSocket, header, sizeof(header) - 1, 0);
	send(clientSocket, buffer, length, 0);

	char end[] = "\r\n\r\n";
	send(clientSocket, end, sizeof(end) - 1, 0);

	std::cout << header << buffer << end << std::endl;




	ifs.close();


}

void	Core::_cdaiTempSendImage()
{
	
	std::ifstream ifs("./temp.png", std::ifstream::binary);

	ifs.seekg (0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg (0, ifs.beg);

	char * buffer = new char [length];

    std::cout << "Reading " << length << " characters... ";
    // read data as a block:
    ifs.read (buffer,length);
//	buffer[length] = 0;

	
//    if (ifs)
//      std::cout << buffer << std::endl;
//    else
//      std::cout << "error: only " << ifs.gcount() << " could be read";
	
	ClientSocket & cs = _client.back();
	int clientSocket = cs.getSocket();

	char header[] =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: image/png\r\n"
		"Content-Length: 18271\r\n"
		//"Connection: keep-alive\r\n"
		"\r\n";

	send(clientSocket, header, sizeof(header) - 1, 0);
	write(1, buffer, length);
	write(clientSocket, buffer, length);
//	send(clientSocket, buffer, length, 0);

	char end[] = "\r\n\r\n";
	send(clientSocket, end, sizeof(end) - 1, 0);

	std::cout << header << buffer << end << std::endl;




	ifs.close();

	delete[] buffer;


}

void	Core::_cdaiTempSendFavicon()
{
	std::ifstream ifs("./favicon.ico", std::ifstream::binary);

	ifs.seekg (0, ifs.end);
    int length = ifs.tellg();
    ifs.seekg (0, ifs.beg);

	char * buffer = new char [length];

    std::cout << "Reading " << length << " characters... ";
    // read data as a block:
    ifs.read (buffer,length);
//	buffer[length] = 0;

	
//    if (ifs)
//      std::cout << buffer << std::endl;
//    else
//      std::cout << "error: only " << ifs.gcount() << " could be read";
	
	ClientSocket & cs = _client.back();
	int clientSocket = cs.getSocket();

	char header[] =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: image/x-icon\r\n"
		"Content-Length: 5539\r\n"
		//"Connection: keep-alive\r\n"
		"\r\n";

	send(clientSocket, header, sizeof(header) - 1, 0);
	write(1, buffer, length);
	write(clientSocket, buffer, length);
//	send(clientSocket, buffer, length, 0);

	char end[] = "\r\n\r\n";
	send(clientSocket, end, sizeof(end) - 1, 0);

	std::cout << header << buffer << end << std::endl;




	ifs.close();

	delete[] buffer;
}
