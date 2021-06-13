/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:22:23 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/13 17:51:11 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER
# define SERVER

# include <vector>
# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <exception>
# include "ServerSocket.hpp"
# include "unistd.h"
# include "cstring"


class Server
{
public:

	Server(void);
	Server(std::string root, int port = 80);
	Server(Server const & src);
	virtual ~Server(void);
	Server &	operator=(Server const &rhs);

	void	addPort(int port);
	void	start();

private:
	std::string					_name;
	std::vector<ServerSocket>	_serverSockets;
	// int							_clientSocket;
	std::vector<int>			_clientSockets;
	// int							_bodySize;
	// std::string					_pathErrorPage;
	std::string					_root;
	// bool						_autoindex;
	int							_worker;
	
};

#endif
