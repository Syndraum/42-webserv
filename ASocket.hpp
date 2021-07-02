/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:44:07 by cdai              #+#    #+#             */
/*   Updated: 2021/07/01 15:14:38 by mchardin         ###   ########.fr       */
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
	protected:
		int						_socket;
		sockaddr_in				_address;

	public:
		
		virtual ~ASocket(void);

		int						get_socket(void) const;
		void					set_socket(int socket);
		const sockaddr_in &		get_address(void) const;
		void					set_address(const sockaddr_in & Address);
		int						get_next_line(std::string & str);
};

#endif
