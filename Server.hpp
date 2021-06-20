/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:22:23 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/20 11:14:28 by syndraum         ###   ########.fr       */
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
	
	Server &	setName(std::string name);
	Server &	setRoot(std::string root);
	Server &	setAutoIndex(bool autoIndex);
	Server &	setClientMaxBodySize(int limit);
	Server &	setPathErrorPage(std::string path);
	void	print();

private:
	std::vector<int>	_activePort;
	std::vector<int>	_activeSocket;
	std::string			_name;
	port_vector			_serverSockets;
	std::string			_root;
	bool				_autoIndex;
	int					_clientMaxBodySize;
	std::string			_pathErrorPage;
};

#endif
