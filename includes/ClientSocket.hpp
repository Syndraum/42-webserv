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

	public:

		ClientSocket(void);
		ClientSocket(ClientSocket const & src);
		virtual ~ClientSocket(void);
		ClientSocket &	operator=(ClientSocket const &rhs);
};

#endif
