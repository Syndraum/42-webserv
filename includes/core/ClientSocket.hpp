/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:56 by syndraum          #+#    #+#             */
/*   Updated: 2021/11/19 21:09:40 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_SOCKET_HPP
# define CLIENT_SOCKET_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include "ASocket.hpp"
# include "Request.hpp"
# include "Server.hpp"
# include <sstream>

class ClientSocket : public ASocket
{
	public:

		ClientSocket(void);
		ClientSocket(ClientSocket const & src);
		virtual ~ClientSocket(void);
		ClientSocket &	operator=(ClientSocket const &rhs);

		std::string		get_ip();
};

#endif
