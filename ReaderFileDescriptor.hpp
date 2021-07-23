/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReaderFileDescriptor.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:06:02 by cdai              #+#    #+#             */
/*   Updated: 2021/07/23 12:07:44 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READERFILEDESCRIPTOR
#define READERFILEDESCRIPTOR

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <unistd.h>
# include "AReaderFileDescriptor.hpp"

class ReaderFileDescriptor : public AReaderFileDescriptor
{
	private:


	public:
		ReaderFileDescriptor(void);
		ReaderFileDescriptor(ReaderFileDescriptor const &);
		virtual ~ReaderFileDescriptor(void);
		ReaderFileDescriptor const & operator=(ReaderFileDescriptor const &);

		virtual int get_next_line(std::string & line);
}

#endif
