/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:48 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/21 14:16:55 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE
# define CORE

# include "Server.hpp"
# include <vector>
# include "ClientSocket.hpp"
# include <poll.h>
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
	void	addServer(Server & server);
	void	addServer();
	Server	&	getServer(int index = 0);

	void	print();

private:

	void				_acceptConnection();
	void				_detectCloseConnection();
	void				_detectResetServerPollFD();
	void				_cdaiTempSendResponse();
	void				_cdaiTempSendImage();

	std::vector<Server>	_servers;
	int					_worker;
	int					_nbActive;
	std::vector<int>	_serverSockets;
	client_vector		_client;
	int					_SIZE_SOCK_ADDR = sizeof(struct sockaddr_in);
	struct pollfd *		_fds;
	int					_nbFds;
};

#endif
