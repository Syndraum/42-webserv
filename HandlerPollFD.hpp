/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerPollFD.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:49:36 by cdai              #+#    #+#             */
/*   Updated: 2021/07/20 12:22:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLL_FD_HANDLER_HPP
#define POLL_FD_HANDLER_HPP

# include <vector>
# include "Server.hpp"
# include "ServerSocket.hpp"
# include "ClientSocket.hpp"
# include <poll.h>

class HandlerPollFD
{
	public:
		typedef std::vector<struct pollfd>	pollfd_vector;
	private:
		int				_SIZE_SOCK_ADDR;
		pollfd_vector	_pfd;

		int				_get_client_socket(std::vector<ClientSocket> &, int);
		void			_add_clients_pfd(int fd, short event);
	public:
		HandlerPollFD(void);
		HandlerPollFD(HandlerPollFD &);
		virtual ~HandlerPollFD(void);
		HandlerPollFD &			operator=(HandlerPollFD &);

		pollfd_vector &			get_pfd(void);
		void					set_pfd(pollfd_vector &);

		struct pollfd			pollfd_init(int fd, short event);
		void					init(std::vector<Server> & servers);
		int						watch(void);
		void					accept_connection(std::vector<Server> & servers, std::vector<ClientSocket> & clients);
		void					erase(void);

		

};

#endif
