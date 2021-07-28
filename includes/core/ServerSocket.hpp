/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:14:00 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/28 18:19:57 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_SOCKET_HPP
# define SERVER_SOCKET_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include "ASocket.hpp"

# include <iostream>
# include <cerrno>
# include <cstring>

class ServerSocket : public ASocket
{
	private:

		int				_port;
		
	public:
	
		ServerSocket(int port = 80);
		ServerSocket(ServerSocket const & src);
		virtual ~ServerSocket(void);
		ServerSocket &	operator=(ServerSocket const &rhs);

		void			setup_socket();
		void			bind_socket();
		void			listen_socket(int worker_connection);

		ServerSocket *	set_port(int port);
		int				get_port() const;
		void			print() const;
};

#endif
