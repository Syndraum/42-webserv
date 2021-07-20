/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerPollFD.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:58:45 by cdai              #+#    #+#             */
/*   Updated: 2021/07/20 12:27:08 by user42           ###   ########.fr       */
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
		for (Server::port_map::iterator it = server.get_server_socket().begin(); 
			it != server.get_server_socket().end(); it++)
		{
			ServerSocket & server_socket = it->second;

			fd = server_socket.get_socket();
			pfd = pollfd_init(fd, POLLIN);
server_socket.set_id(server_id); // should not be here
			_pfd.push_back(pfd);
			server_id++;
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
HandlerPollFD::accept_connection(std::vector<Server> & servers, std::vector<ClientSocket> & clients)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		Server & server = servers[i];
		for (
			Server::port_map::iterator it = server.get_server_socket().begin();
			it != server.get_server_socket().end();
			it++
		)
		{
			ServerSocket & server_socket = it->second;
			int fd = server_socket.get_socket();

			if (
				_pfd[server_socket.get_id()].revents == POLLIN
			)
			{
				clients.push_back(ClientSocket(server));
				_get_client_socket(clients, fd);
			}
		}
	}
}

int
HandlerPollFD::_get_client_socket(std::vector<ClientSocket> & clients, int fd)
{
	int new_socket;
	int one = 1;
	ClientSocket & cs = clients.back();

	if ((new_socket = accept(fd, (struct sockaddr *)&cs.get_address() , reinterpret_cast<socklen_t*>(&_SIZE_SOCK_ADDR))) < 0)
	{
		perror("accept failed");
		exit(EXIT_FAILURE);
	}
	setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
	std::cout << "New connection, socket fd is " << new_socket << ", socket server :" << fd << std::endl;
	cs.set_socket(new_socket);
	std::cout << "Adding to list of sockets as " << clients.size() << std::endl;
	_add_clients_pfd(new_socket, POLLOUT);
	return (new_socket);
}
