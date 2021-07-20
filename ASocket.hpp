/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocket.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 16:44:07 by cdai              #+#    #+#             */
/*   Updated: 2021/07/20 17:16:13 by cdai             ###   ########.fr       */
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
		char					_buffer[BUFFER_SIZE];
		int						_id;

	public:
		
		ASocket(void);
		ASocket(ASocket const &);
		virtual ~ASocket(void);
		ASocket const &	operator=(ASocket const &);

		int						get_socket(void) const;
		void					set_socket(int socket);
		const sockaddr_in &		get_address(void) const;
		void					set_address(const sockaddr_in & Address);
		int						get_next_line(std::string & str);
		int						get_id() const;
		void					set_id(int id);
		void					reset_buffer(void);
		void					read_body(std::string &, int);
		void					read_until_end(void);
};

#endif
