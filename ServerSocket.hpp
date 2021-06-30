/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:14:00 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/30 15:08:44 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERSOCKET
# define SERVERSOCKET

# include <sys/socket.h>
# include <netinet/in.h>
# include "ASocket.hpp"

# include <iostream>
# include <cerrno>
# include <cstring>

class ServerSocket : public ASocket
{
public:
	ServerSocket(int port = 80);
	ServerSocket(ServerSocket const & src);
	virtual ~ServerSocket(void);
	ServerSocket &	operator=(ServerSocket const &rhs);

	void			setup_socket();
	void			bind_socket();
	void			listen_socket(int worker_connection);

	ServerSocket *	set_port(int port);
	int				get_port();
	void			print();

private:
	int			_port;
};

#endif
