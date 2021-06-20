/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:22:23 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/20 00:02:07 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER
# define SERVER

# include <vector>
# include <map>
# include <utility>
# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <exception>
# include "ServerSocket.hpp"
# include "unistd.h"
# include "cstring"
# include <algorithm>


class Server
{
public:

	typedef std::map<int, ServerSocket>		port_vector;

	Server(void);
	Server(std::string root, int port = 8080);
	Server(Server const & src);
	virtual ~Server(void);
	Server &	operator=(Server const &rhs);

	Server &	addPort(int port);
	void	start(int worker);

	ServerSocket &		getServerSocket(int port);
	std::vector<int> &	getActiveSocket();


	void	print();

private:
	std::vector<int>	_activePort;
	std::vector<int>	_activeSocket;
	std::string			_name;
	port_vector			_serverSockets;
	std::string			_root;
	
};

#endif
