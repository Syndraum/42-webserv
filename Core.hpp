/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:48 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/16 20:49:59 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE
# define CORE

# include "Server.hpp"
# include <vector>
# include "ClientSocket.hpp"
# include <poll.h>
# include "Response.hpp"
# include "Request.hpp"
# include "BuilderRequest.hpp"
# include "MethodGet.hpp"
# include "MethodDelete.hpp"
# include "MethodLibrary.hpp"
# include "Extension.hpp"
# include "HandlerPollFD.hpp"


class Core
{
	public:
		typedef std::vector<ClientSocket>	client_vector;

	private:

		HandlerPollFD						_pfdh;
		std::vector<Server>					_servers;
		int									_worker;
		std::vector<int>					_server_sockets;
		client_vector						_client;
		int									_SIZE_SOCK_ADDR;
		MethodLibrary						_methods;
		BuilderRequest						_br;
		Extension *							_extension;

		void								_accept_connection();
		void								_handle_request_and_detect_close_connection();
		void								_detect_reset_server_poll_fd();

	public:

		Core(void);
		Core(Core const & src);
		virtual ~Core(void);
		Core &								operator=(Core const &rhs);

		void								start();
		void								add_server(Server & server);
		Server &							add_server();
		Server const &						get_server(int index = 0) const;
		Core &								add_method(AMethod *);
		AMethod	*							get_method(const std::string &) const;
		Core &								set_worker(int);
		int									get_worker(void) const;
		void								set_extension(Extension * extensoin);
		// CsvReader &							get_csv_reader();
		void								print() const;
};

#endif
