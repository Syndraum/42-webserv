/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerPollFD.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:49:36 by cdai              #+#    #+#             */
/*   Updated: 2021/07/19 16:06:07 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLL_FD_HANDLER_HPP
#define POLL_FD_HANDLER_HPP

# include <vector>
# include "Server.hpp"
# include "ServerSocket.hpp"
# include "poll.h"

class HandlerPollFD
{
	public:
		typedef std::vector<struct pollfd>	pollfd_vector;
	private:
		pollfd_vector	_pfd;

		
	public:
		HandlerPollFD(void);
		HandlerPollFD(HandlerPollFD &);
		virtual ~HandlerPollFD(void);
		HandlerPollFD & operator=(HandlerPollFD &);

		pollfd_vector &			get_pfd(void);
		void					set_pfd(pollfd_vector &);


		struct pollfd			pollfd_init(int fd, short event);
		void					add_clients_pfd(int fd, short event);
		void					init(std::vector<Server> & servers);


		void					erase(int fd);

		

};

#endif
