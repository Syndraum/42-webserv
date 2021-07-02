/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:56 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/01 15:21:37 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET
# define CLIENTSOCKET

# include <sys/socket.h>
# include <netinet/in.h>
# include "ASocket.hpp"
# include "Request.hpp"

class ClientSocket : public ASocket
{
		Request		_request;
	public:

		ClientSocket(void);
		ClientSocket(ClientSocket const & src);
		virtual ~ClientSocket(void);
		ClientSocket &	operator=(ClientSocket const &rhs);

		Request &	get_request();
};

#endif
