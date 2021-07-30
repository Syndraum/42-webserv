/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:14:00 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/29 18:55:08 by mchardin         ###   ########.fr       */
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
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

class ServerSocket : public ASocket
{
	private:

		int					_port;
		std::string			_ip;
		bool				_active;
		
	public:
	
		ServerSocket(int port = 80);
		ServerSocket(int port, std::string ip);
		ServerSocket(ServerSocket const & src);
		virtual ~ServerSocket(void);
		ServerSocket &	operator=(ServerSocket const &rhs);

		void				setup_socket();
		void				bind_socket();
		void				listen_socket(int worker_connection);

		ServerSocket *		set_port(int port);
		int					get_port() const;
		const std::string &	get_ip() const;
		ServerSocket *		set_active(bool);
		bool				get_active() const;
		void				print() const;
};

#endif
