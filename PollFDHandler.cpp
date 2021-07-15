/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollFDHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:58:45 by cdai              #+#    #+#             */
/*   Updated: 2021/07/15 17:51:12 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollFDHandler.hpp"

// value given to poll (nbFds)
int PollFDHandler::start(std::vector<struct pollfd> & fds, std::vector<Server> & servers, std::vector<ClientSocket> & clients)
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
			fds.push_back(pfd);
			nb_pfd++;
		}
	}
	std::cout << "nb_pfd: " << nb_pfd << std::endl;
	for (size_t i = 0; i < clients.size(); i++)
	{
		fd = clients[i].get_socket();

		pfd = pollfd_init(fd, POLLOUT);
		clients[i].set_id(nb_pfd);
		fds.push_back(pfd);
		nb_pfd++;
	}
	return fds.size();
}

struct pollfd	PollFDHandler::pollfd_init(int fd, short event)
{
	struct pollfd pfd;

	pfd.fd = fd;
	pfd.events = event;
	pfd.revents = 0;
	return (pfd);
}

void	PollFDHandler::reset_pfd(std::vector<struct pollfd> & fds)
{
	for (std::vector<struct pollfd>::iterator it = fds.begin(); 
		it != fds.end(); it++)
	{
		it->revents = 0;
	}
}
