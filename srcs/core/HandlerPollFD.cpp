/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerPollFD.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:58:45 by cdai              #+#    #+#             */
/*   Updated: 2021/11/12 14:23:30 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandlerPollFD.hpp"

HandlerPollFD::HandlerPollFD() : _pfd(), _fd_server_max(-1), _hr(0)
{
	_SIZE_SOCK_ADDR = sizeof(struct sockaddr_in);
}

HandlerPollFD::HandlerPollFD(HandlerPollFD & rhs)
{
	*this = rhs;
}

HandlerPollFD::~HandlerPollFD(void)
{}

HandlerPollFD & HandlerPollFD::operator=(HandlerPollFD & rhs)
{
	if (this != &rhs){
		this->_pfd = rhs._pfd;
		this->_hr = rhs._hr;
		this->_fd_server_max = rhs._fd_server_max;
	}
	return (*this);
}

struct pollfd	HandlerPollFD::pollfd_init(int fd, short event)
{
	struct pollfd pfd;

	pfd.fd = fd;
	pfd.events = event;
	pfd.revents = 0;
	return (pfd);
}

HandlerPollFD::pollfd_vector &
HandlerPollFD::get_pfd(void)
{
	return _pfd;
}

void
HandlerPollFD::set_pfd(HandlerPollFD::pollfd_vector & pfd)
{
	_pfd = pfd;
}

void
HandlerPollFD::set_hr(HandlerRequest & hr)
{
	_hr = &hr;
}

void
HandlerPollFD::_add_clients_pfd(int fd, short event)
{
	struct pollfd pfd = pollfd_init(fd, event);
	_pfd.push_back(pfd);
}


void
HandlerPollFD::init(std::vector<Server> & servers)
{
	int fd;
	struct pollfd pfd;

	for (size_t i = 0; i < servers.size(); i++)
	{
		Server & server = servers[i];
		for (Server::port_map::iterator it = server.get_map_socket().begin(); 
			it != server.get_map_socket().end(); it++)
		{
			ServerSocket & server_socket = it->second;

			if (server_socket.get_active())
			{
				fd = server_socket.get_socket();
				pfd = pollfd_init(fd, POLLIN);
				_pfd.push_back(pfd);
				if (fd > _fd_server_max)
					_fd_server_max = fd;
			}
		}
	}
}

// void
// HandlerPollFD::erase(void)
// {
// 	for (pollfd_vector::iterator it = _pfd.begin(); it != _pfd.end(); it++)
// 		if (it->revents == POLLOUT)
// 		{
// 			_pfd.erase(it);
// 			return ;
// 		}
// }

void
HandlerPollFD::remove(int socket)
{
	for (pollfd_vector::iterator it = _pfd.begin(); it != _pfd.end(); it++)
	if (it->fd == socket)
	{
		_pfd.erase(it);
		return ;
	}
}

int
HandlerPollFD::watch(void)
{
	return (poll(&(_pfd.front()), _pfd.size(), 60000));
}

int
HandlerPollFD::handle(std::vector<Server> & servers, std::vector<Client> & clients)
{
	for (size_t i = 0; i < _pfd.size(); i++)
	{
		if (_pfd[i].revents == POLLIN)
		{
			if (_fd_server_max < _pfd[i].fd)
			{
				Client & client = *find_client_by_socket(clients, _pfd[i].fd);
				if (_hr->handle(client, servers) == -1)
				{
					// std::cout << "AWAIT on " << _pfd[i].fd << std::endl;
					_pfd[i].revents = 0;
				}
				else
				{
					// std::cout << "close fd " << client.get_socket() << std::endl;
					close(client.get_socket());
					remove(client.get_socket());
					clients.erase(std::find<std::vector<Client>::iterator, Client>(clients.begin(), clients.end(), client));
					return (1);
				}
			}
			else
			{
				Server * server = find_server_by_socket(servers, _pfd[i].fd);

				clients.push_back(Client(*server, *(server->find_socket(_pfd[i].fd))));
				_accept_connection(clients, _pfd[i].fd);
			}
		}
	}
	return (0);
}

void
HandlerPollFD::reset_server(void)
{
	for (pollfd_vector::iterator it = _pfd.begin(); it != _pfd.end(); it++)
	{
		if (it->events == POLLIN)
			it->revents = 0;
	}
}

Server *
HandlerPollFD::find_server_by_socket(std::vector<Server> & servers, int socket)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		for (
			Server::port_map::iterator it = servers[i].get_map_socket().begin();
			it != servers[i].get_map_socket().end();
			it++
		)
		{
			if (it->second.get_socket() == socket)
				return (&servers[i]);
		}
	}
	return (0);
}

Client *
HandlerPollFD::find_client_by_socket(std::vector<Client> & clients, int socket)
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		if (clients[i].get_socket() == socket)
			return (&clients[i]);
	}
	return (0);
}

int
HandlerPollFD::_accept_connection(std::vector<Client> & clients, int server_socket)
{
	int			one			= 1;
	int			new_socket	= -1;
	Client &	new_client	= clients.back();

	if ((new_socket = accept(server_socket, (struct sockaddr *)&new_client.get_socket_struct().get_address() , reinterpret_cast<socklen_t*>(&_SIZE_SOCK_ADDR))) < 0)
	{
		perror("accept failed");
		exit(EXIT_FAILURE);
	}
	setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
	std::cout << "[server socket : " << server_socket << "] New connection, " << new_client.get_socket_struct().get_ip() << " accept on socket "<< new_socket << std::endl;
	new_client.get_socket_struct().set_socket(new_socket);
	// std::cout << "Adding to list of sockets as " << clients.size() << std::endl;
	_add_clients_pfd(new_socket, POLLIN);
	std::cout << "the previous socket is : " << clients.begin()->get_socket_struct().get_socket() << std::endl;
	return (new_socket);
}

