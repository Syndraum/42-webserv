/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:48 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/30 14:42:58 by mchardin         ###   ########.fr       */
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
// cdai_temp
# include <fstream>

class Core
{
public:
	typedef std::vector<ClientSocket> client_vector;

	Core(void);
	Core(Core const & src);
	virtual ~Core(void);
	Core &	operator=(Core const &rhs);

	void	start();
	void	add_server(Server & server);
	Server	&	add_server();
	Server	&	get_server(int index = 0);
	Core	&	add_method(AMethod *);
	AMethod	*	get_method(const std::string &);

	void	print();

private:

	void				_accept_connection();
	void				_handle_request_and_detect_close_connection();
	void				_detect_reset_server_poll_fd();

	std::vector<Server>	_servers;
	int					_worker;
	int					_nb_active;
	std::vector<int>	_server_sockets;
	client_vector		_client;
	int					_SIZE_SOCK_ADDR;
	struct pollfd *		_fds;
	int					_nb_fds;
	MethodLibrary		_methods;
};

#endif
