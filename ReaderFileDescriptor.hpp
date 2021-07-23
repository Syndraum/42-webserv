/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReaderFileDescriptor.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:06:02 by cdai              #+#    #+#             */
/*   Updated: 2021/07/23 17:11:25 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_FILE_DESCRIPTOR
#define READER_FILE_DESCRIPTOR

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <unistd.h>
# include "AReaderFileDescriptor.hpp"

class ReaderFileDescriptor : public AReaderFileDescriptor
{
	private:
		ReaderFileDescriptor(void);


	public:
		ReaderFileDescriptor(int);
		ReaderFileDescriptor(ReaderFileDescriptor const &);
		virtual ~ReaderFileDescriptor(void);
		ReaderFileDescriptor const & operator=(ReaderFileDescriptor const &);

		virtual int _read(void);
};

#endif
