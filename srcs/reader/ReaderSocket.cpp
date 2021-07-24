/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReaderSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:45:01 by cdai              #+#    #+#             */
/*   Updated: 2021/07/24 18:28:02 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReaderSocket.hpp"

ReaderSocket::ReaderSocket(int fd):
AReaderFileDescriptor(fd)
{}

ReaderSocket::ReaderSocket(ReaderSocket const & rhs)
{
	*this = rhs;
}

ReaderSocket::~ReaderSocket(void)
{}

ReaderSocket const & ReaderSocket::operator=(ReaderSocket const & rhs)
{
	if (&rhs != this)
	{
		AReaderFileDescriptor::operator=(rhs);
	}
	return (*this);
}

int
ReaderSocket::_read(void)
{
	return (recv(_fd, _buffer, BUFFER_SIZE - 1, MSG_DONTWAIT));
}
