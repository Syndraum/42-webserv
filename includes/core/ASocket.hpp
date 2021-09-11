/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:44:07 by cdai              #+#    #+#             */
/*   Updated: 2021/07/29 16:52:26 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASOCKET_HPP
#define ASOCKET_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <unistd.h>
# include "ReaderSocket.hpp"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 32
#endif

class ASocket
{
	protected:
		int						_socket;
		sockaddr_in				_address;
		ReaderSocket			_reader;

		void					set_reader(ReaderSocket &);
	public:
		
		ASocket(void);
		ASocket(ASocket const &);
		virtual ~ASocket(void);
		ASocket const &	operator=(ASocket const &);

		int						get_socket(void) const;
		void					set_socket(int socket);
		const sockaddr_in &		get_address(void) const;
		void					set_address(const sockaddr_in & Address);
		ReaderSocket &			get_reader(void);
};

#endif
