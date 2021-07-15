/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollFDHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:49:36 by cdai              #+#    #+#             */
/*   Updated: 2021/07/15 17:42:19 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLL_FD_HANDLER_HPP
#define POLL_FD_HANDLER_HPP

# include <vector>
# include "Server.hpp"
# include "ClientSocket.hpp"
# include "ServerSocket.hpp"
# include "poll.h"

class PollFDHandler
{
	private:
		PollFDHandler(void);
		PollFDHandler(PollFDHandler const &);
		virtual ~PollFDHandler(void);
		PollFDHandler & operator=(PollFDHandler const &);
	public:
		static struct pollfd	pollfd_init(int fd, short event);
		static int				start(std::vector<struct pollfd> &, std::vector<Server> &, std::vector<ClientSocket> &);
		static void				reset_pfd(std::vector<struct pollfd> & fds);
		

};

#endif
