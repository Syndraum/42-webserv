/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:56 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/07 11:38:08 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET
# define CLIENTSOCKET

# include <sys/socket.h>
# include <netinet/in.h>
# include "ASocket.hpp"
# include "Request.hpp"
# include "Server.hpp"

class ClientSocket : public ASocket
{
	private:
		
		Request		_request;
		Server &	_server;

		ClientSocket(void);
	public:

		ClientSocket(Server &);
		ClientSocket(ClientSocket const & src);
		virtual ~ClientSocket(void);
		ClientSocket &	operator=(ClientSocket const &rhs);

		Request &	get_request();
		Server &	get_server();
};

#endif
