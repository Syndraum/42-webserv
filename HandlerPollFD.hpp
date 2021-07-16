/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerPollFD.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:49:36 by cdai              #+#    #+#             */
/*   Updated: 2021/07/16 19:59:46 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLL_FD_HANDLER_HPP
#define POLL_FD_HANDLER_HPP

# include <vector>
# include "Server.hpp"
# include "ClientSocket.hpp"
# include "ServerSocket.hpp"
# include "poll.h"

class HandlerPollFD
{
	public:
		typedef std::vector<struct pollfd>	pollfd_vector;
	private:
		pollfd_vector	_servers_pfd;
		pollfd_vector	_clients_pfd;
		pollfd_vector	_all_pfd;

		
	public:
		HandlerPollFD(void);
		HandlerPollFD(HandlerPollFD &);
		virtual ~HandlerPollFD(void);
		HandlerPollFD & operator=(HandlerPollFD &);

		pollfd_vector &			get_servers_pfd(void);
		void					set_servers_pfd(pollfd_vector &);
		pollfd_vector &			get_clients_pfd(void);
		void					set_clients_pfd(pollfd_vector &);
		pollfd_vector &			get_all_pfd(void);
		void					set_all_pfd(pollfd_vector &);


		struct pollfd			pollfd_init(int fd, short event);
		void					add_clients_pfd(int fd, short event);
		void					init(std::vector<Server> & servers);


		void					erase(int fd);

		

};

#endif
