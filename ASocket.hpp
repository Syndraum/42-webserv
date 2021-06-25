/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:44:07 by cdai              #+#    #+#             */
/*   Updated: 2021/06/25 17:45:37 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASOCKET
#define ASOCKET

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <unistd.h>

class ASocket
{
public:
	
	virtual ~ASocket(void);

	int		get_socket(void) const;
	void	set_socket(int socket);
	int		get_next_line(std::string & str);

protected:
	int			_socket;
	sockaddr_in	address;

};

#endif
