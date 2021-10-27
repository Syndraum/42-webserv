/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReaderFileDescriptor.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:06:02 by cdai              #+#    #+#             */
/*   Updated: 2021/07/28 18:51:46 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_FILE_DESCRIPTOR_HPP
# define READER_FILE_DESCRIPTOR_HPP

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

		virtual int _read(int n_read = BUFFER_SIZE - 1);
};

#endif
