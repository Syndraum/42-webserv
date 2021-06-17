#include "Core.hpp"

Core::Core(void) : _worker(3), _maxfd(-1), _nbActive(0)
{
	_clientSockets.insert(_clientSockets.begin(), _worker, 0);
}

Core::Core(Core const & src)
{
	*this = src;
}

Core::~Core(void)
{
	
}

Core &	Core::operator=(Core const & rhs)
{
	if (&rhs != this)
		this->_worker = rhs._worker;
	return *this;
}

void	Core::start(){
	int new_socket = -1;
	int c = sizeof(struct sockaddr_in);
	int fd;
	std::vector<int> activeSocket;

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
	// int main_fd = _servers[0].getServerSocket(8080).getSocket();
	while (true)
	{
		FD_ZERO(&_readfds);
		for (size_t i = 0; i < _serverSockets.size(); i++)
		{
			fd = _serverSockets[i];
			FD_SET(fd, &_readfds);
			if(fd > _maxfd)
				_maxfd = fd;
		}
		for (size_t i = 0; i < _clientSockets.size(); i++)
		{
			int fd = _clientSockets[i];
			if(fd > 0)
				FD_SET(fd, &_readfds);
			if(fd > _maxfd)
				_maxfd = fd;
		}
		_nbActive = select( _maxfd + 1, &_readfds, NULL, NULL, NULL);
		for (size_t i = 0; i < _serverSockets.size(); i++)
		{
			int fd = _serverSockets[i];
			if (FD_ISSET(fd, &_readfds))
			{
				if ((new_socket = accept(fd, reinterpret_cast<sockaddr*>(&_servers[0].getServerSocket(8080).getServer()) , reinterpret_cast<socklen_t*>(&c))) < 0)
				{
					perror("accept failed");
					exit(EXIT_FAILURE);
				}
				std::cout << "New connection, socket fd is " << new_socket << std::endl;
				for (int i = 0; i < _worker; i++)
				{  
					//if position is empty 
					if( _clientSockets[i] == 0 )  
					{  
						_clientSockets[i] = new_socket;  
						printf("Adding to list of sockets as %d\n" , i);  
							
						break;  
					}
				} 
			}
		}
		// if (FD_ISSET(main_fd, &_readfds))
		// {
		// 	if ((new_socket = accept(main_fd, reinterpret_cast<sockaddr*>(&_servers[0].getServerSocket(8080).getServer()) , reinterpret_cast<socklen_t*>(&c))) < 0)
		// 	{
		// 		perror("accept failed");
		// 		exit(EXIT_FAILURE);
		// 	}
		// 	std::cout << "New connection, socket fd is " << new_socket << std::endl;
		// 	for (int i = 0; i < _worker; i++)
		// 	{  
		// 		//if position is empty 
		// 		if( _clientSockets[i] == 0 )  
		// 		{  
		// 			_clientSockets[i] = new_socket;  
		// 			printf("Adding to list of sockets as %d\n" , i);  
						
		// 			break;  
		// 		}
		// 	} 
		// }
		for (int i = 0; i < _worker; i++)  
		{
			int fd = _clientSockets[i];  
			int valread;
			char buffer[1025];
					
			if (FD_ISSET( fd , &_readfds))  
			{  
				//Check if it was for closing , and also read the 
				//incoming message 
				if ((valread = read( fd , buffer, 1024)) == 0)  
				{    
					std::cout << "Host disconnected" << std::endl;  

					close( fd );  
					_clientSockets[i] = 0;  
				}  
						
				//Echo back the message that came in 
				else 
				{  
					//set the string terminating NULL byte on the end 
					//of the data read 
					buffer[valread] = '\0';  
					send(fd , buffer , std::strlen(buffer) , 0 );  
				}  
			}
		} 
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
