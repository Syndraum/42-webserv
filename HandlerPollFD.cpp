/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerPollFD.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:58:45 by cdai              #+#    #+#             */
/*   Updated: 2021/07/16 20:05:42 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandlerPollFD.hpp"

HandlerPollFD::HandlerPollFD(void)
{
	
}

HandlerPollFD::HandlerPollFD(HandlerPollFD & rhs)
{
	*this = rhs;
}

HandlerPollFD::~HandlerPollFD(void)
{
	
}

HandlerPollFD & HandlerPollFD::operator=(HandlerPollFD & rhs)
{
	_servers_pfd = rhs._servers_pfd;
	_clients_pfd = rhs._clients_pfd;
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

HandlerPollFD::pollfd_vector & HandlerPollFD::get_servers_pfd(void)
{
	return _servers_pfd;
}

void	HandlerPollFD::set_servers_pfd(HandlerPollFD::pollfd_vector & servers_pfd)
{
	_servers_pfd = servers_pfd;
}

HandlerPollFD::pollfd_vector & HandlerPollFD::get_clients_pfd(void)
{
	return _clients_pfd;
}

void	HandlerPollFD::set_clients_pfd(HandlerPollFD::pollfd_vector & clients_pfd)
{
	_clients_pfd = clients_pfd;
}

HandlerPollFD::pollfd_vector & HandlerPollFD::get_all_pfd(void)
{
	return _all_pfd;
}

void	HandlerPollFD::set_all_pfd(HandlerPollFD::pollfd_vector & all_pfd)
{
	_all_pfd = all_pfd;
}

void	HandlerPollFD::add_clients_pfd(int fd, short event)
{
	struct pollfd pfd = pollfd_init(fd, event);

	_clients_pfd.push_back(pfd);
	_all_pfd.push_back(pfd);
}


void HandlerPollFD::init(std::vector<Server> & servers)
{
	int fd;
	struct pollfd pfd;
	int nb_pfd = 0;

	for (size_t i = 0; i < servers.size(); i++)
	{
		Server & server = servers[i];
		for (Server::port_map::iterator it = server.get_server_socket().begin(); 
			it != server.get_server_socket().end(); it++)
		{
			ServerSocket & server_socket = it->second;

			fd = server_socket.get_socket();
			pfd = pollfd_init(fd, POLLIN);
			server_socket.set_id(nb_pfd);
			_servers_pfd.push_back(pfd);
			_all_pfd.push_back(pfd);
			nb_pfd++;
		}
	}
}

void	HandlerPollFD::erase(int fd)
{
	for (pollfd_vector::iterator it = _clients_pfd.begin(); it != _clients_pfd.end(); it++)
	{
		if (it->fd == fd)
		{
			_clients_pfd.erase(it);
			break ;
		}
	}
	for (pollfd_vector::iterator it = _all_pfd.begin(); it != _all_pfd.end(); it++)
	{
		if (it->fd == fd)
		{
			_all_pfd.erase(it);
			return ;
		}
	}
}
