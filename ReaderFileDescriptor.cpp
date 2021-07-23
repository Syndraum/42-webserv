/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReaderFileDescriptor.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 12:06:55 by cdai              #+#    #+#             */
/*   Updated: 2021/07/23 17:12:18 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReaderFileDescriptor.hpp"

ReaderFileDescriptor::ReaderFileDescriptor(int fd):
AReaderFileDescriptor(fd)
{}

ReaderFileDescriptor::ReaderFileDescriptor(ReaderFileDescriptor const & rhs)
{
	*this = rhs;
}

ReaderFileDescriptor::~ReaderFileDescriptor(void)
{}

ReaderFileDescriptor const & ReaderFileDescriptor::operator=(ReaderFileDescriptor const & rhs)
{
	if (&rhs != this)
	{
		_fd = rhs._fd;
		for (int i = 0; i < BUFFER_SIZE; i++)
			_buffer[i] = rhs._buffer[i];
	}
	return (*this);
}

int
ReaderFileDescriptor::_read(void)
{
	return (read(_fd, _buffer, BUFFER_SIZE - 1));
}
