/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReaderSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:15:52 by cdai              #+#    #+#             */
/*   Updated: 2021/07/23 12:06:04 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_SOCKET
#define READER_SOCKET

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <unistd.h>
# include "AReaderFileDescriptor.hpp"

class ReaderSocket : public AReaderFileDescriptor
{
	private:
		ReaderSocket(void);


	public:
		ReaderSocket(int fd);
		ReaderSocket(ReaderSocket const &);
		virtual ~ReaderSocket(void);
		ReaderSocket const & operator=(ReaderSocket const &);

		virtual int get_next_line(std::string & line);
		void	read_body(std::string & line, int content_length);
		void	read_until_end(void);
}

#endif
