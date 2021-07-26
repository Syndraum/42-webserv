/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReaderFileDescriptor.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 12:06:55 by cdai              #+#    #+#             */
/*   Updated: 2021/07/25 15:11:38 by cdai             ###   ########.fr       */
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
		AReaderFileDescriptor::operator=(rhs);
	}
	return (*this);
}

int
ReaderFileDescriptor::_read(void)
{
	// std::cout << "readFD" << std::endl;
	return (read(_fd, _buffer, BUFFER_SIZE - 1));
}
