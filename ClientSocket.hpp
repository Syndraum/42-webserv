/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:56 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/17 18:13:57 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENTSOCKET
# define CLIENTSOCKET

# include <sys/socket.h>
# include <netinet/in.h>

class ClientSocket
{
public:

	ClientSocket(void);
	ClientSocket(ClientSocket const & src);
	virtual ~ClientSocket(void);
	ClientSocket &	operator=(ClientSocket const &rhs);

	int			getSocket(void) const;
	void		setSocket(int Socket);
	sockaddr	& getAddress(void);
	void		setAddress(sockaddr & Address);


private:
	int			_socket;
	sockaddr	_address;
};

#endif
