/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:44:07 by cdai              #+#    #+#             */
/*   Updated: 2021/06/30 19:05:20 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASOCKET
#define ASOCKET

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

class ASocket
{
public:
	ASocket(void);
	virtual ~ASocket(void);

	int				get_socket(void) const;
	void			set_socket(int socket);
	sockaddr_in	&	get_address(void);
	void			set_address(sockaddr_in & Address);
	int				get_next_line(std::string & str);
	void			reset_buffer(void);

protected:
	int			_socket;
	sockaddr_in	_address;
	char		_buffer[BUFFER_SIZE];

};

#endif
