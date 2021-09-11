/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerPollFD.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:49:36 by cdai              #+#    #+#             */
/*   Updated: 2021/07/24 18:50:20 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLL_FD_HANDLER_HPP
#define POLL_FD_HANDLER_HPP

# include <vector>
# include "Server.hpp"
# include "Client.hpp"
# include "ServerSocket.hpp"
# include "ClientSocket.hpp"
# include "HandlerRequest.hpp"
# include <poll.h>
# include <algorithm>

class HandlerPollFD
{
	public:
		typedef std::vector<struct pollfd>	pollfd_vector;
	private:
		pollfd_vector	_pfd;
		int				_fd_server_max;
		HandlerRequest	* _hr;
		int				_SIZE_SOCK_ADDR;

		int				_accept_connection(std::vector<Client> &, int);
		void			_add_clients_pfd(int fd, short event);
	public:
		HandlerPollFD(void);
		HandlerPollFD(HandlerPollFD &);
		virtual ~HandlerPollFD(void);
		HandlerPollFD &			operator=(HandlerPollFD &);

		pollfd_vector &			get_pfd(void);
		void					set_pfd(pollfd_vector &);
		void					set_hr(HandlerRequest &);

		struct pollfd			pollfd_init(int fd, short event);
		void					init(std::vector<Server> & servers);
		int						watch(void);
		void					handle(std::vector<Server> & servers, std::vector<Client> & clients);
		void					erase(void);
		void					remove(int);
		void					reset_server(void);
		Server *				find_server_by_socket(std::vector<Server> &, int);
		Client *				find_client_by_socket(std::vector<Client> &, int);
};

# include "Core.hpp"

#endif
