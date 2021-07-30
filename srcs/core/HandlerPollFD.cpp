/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerPollFD.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:58:45 by cdai              #+#    #+#             */
/*   Updated: 2021/07/24 19:12:03 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandlerPollFD.hpp"

HandlerPollFD::HandlerPollFD(void)
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
	_pfd = rhs._pfd;
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
	int server_id = 0;

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
				server_socket.set_id(server_id); // should not be here
				_pfd.push_back(pfd);
				server_id++;
			}
		}
	}
}

void
HandlerPollFD::erase(void)
{
	for (pollfd_vector::iterator it = _pfd.begin(); it != _pfd.end(); it++)
		if (it->revents == POLLOUT)
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

void
HandlerPollFD::accept_connection(std::vector<Server> & servers, std::vector<Client> & clients)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		Server & server = servers[i];
		for (
			Server::port_map::iterator it = server.get_map_socket().begin();
			it != server.get_map_socket().end();
			it++
		)
		{
			ServerSocket & server_socket = it->second;
			if (server_socket.get_active())
			{
				int fd = server_socket.get_socket();

				if (
					_pfd[server_socket.get_id()].revents == POLLIN
				)
				{
					clients.push_back(Client(server, server_socket));
					_get_client_socket(clients, fd);
				}
			}
		}
	}
}

int
HandlerPollFD::_get_client_socket(std::vector<Client> & clients, int fd)
{
	int new_socket = -1;
	int one = 1;
	Client & cs = clients.back();

	if ((new_socket = accept(fd, (struct sockaddr *)&cs.get_socket_struct().get_address() , reinterpret_cast<socklen_t*>(&_SIZE_SOCK_ADDR))) < 0)
	{
		perror("accept failed");
		exit(EXIT_FAILURE);
	}
	setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
	std::cout << "New connection, socket fd is " << new_socket << ", socket server :" << fd << std::endl;
	cs.get_socket_struct().set_socket(new_socket);
	std::cout << "Adding to list of sockets as " << clients.size() << std::endl;
	_add_clients_pfd(new_socket, POLLOUT);
	if (clients.size() > 1)
	{
		std::cout << "the previous socket is : " << clients.begin()->get_socket_struct().get_socket() << std::endl;
	}
	return (new_socket);
}
