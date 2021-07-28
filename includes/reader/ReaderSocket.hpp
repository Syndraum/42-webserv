/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReaderSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:15:52 by cdai              #+#    #+#             */
/*   Updated: 2021/07/28 18:51:51 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_SOCKET_HPP
# define READER_SOCKET_HPP

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

		virtual int	_read(void);
};

#endif
