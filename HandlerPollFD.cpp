/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerPollFD.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:58:45 by cdai              #+#    #+#             */
/*   Updated: 2021/07/16 20:33:24 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandlerPollFD.hpp"

HandlerPollFD::HandlerPollFD(void)
{}

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

HandlerPollFD::pollfd_vector & HandlerPollFD::get_pfd(void)
{
	return _pfd;
}

void	HandlerPollFD::set_pfd(HandlerPollFD::pollfd_vector & _pfd)
{
	_pfd = _pfd;
}

void	HandlerPollFD::add_clients_pfd(int fd, short event)
{
	struct pollfd pfd = pollfd_init(fd, event);
	_pfd.push_back(pfd);
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
			_pfd.push_back(pfd);
			nb_pfd++;
		}
	}
}

void	HandlerPollFD::erase(int fd)
{
	for (pollfd_vector::iterator it = _pfd.begin(); it != _pfd.end(); it++)
	{
		if (it->fd == fd)
		{
			_pfd.erase(it);
			return ;
		}
	}
}
