/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AReaderFileDescriptor.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:22:22 by cdai              #+#    #+#             */
/*   Updated: 2021/07/26 13:38:06 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AReaderFileDescriptor.hpp"

AReaderFileDescriptor::AReaderFileDescriptor(void)
{}

AReaderFileDescriptor::AReaderFileDescriptor(int fd):
_fd(fd)
{
	_reset_buffer();
}

AReaderFileDescriptor::AReaderFileDescriptor(AReaderFileDescriptor const & rhs)
{
	*this = rhs;
}

AReaderFileDescriptor::~AReaderFileDescriptor(void)
{}

AReaderFileDescriptor const &
AReaderFileDescriptor::operator=(AReaderFileDescriptor const & rhs)
{
	_fd = rhs._fd;
	for (int i = 0; i < BUFFER_SIZE; i++)
		_buffer[i] = rhs._buffer[i];
	return *this;
}

void
AReaderFileDescriptor::_reset_buffer(void)
{
	// std::cout << "----------RESET BUFFER--------" << std::endl;
	for (int i = 0; i < BUFFER_SIZE; i++)
		_buffer[i] = '\0';
}

std::string
AReaderFileDescriptor::get_buffer(void) const
{
	return (_buffer);
}

int
AReaderFileDescriptor::get_fd(void)
{
	return (_fd);
}

void
AReaderFileDescriptor::set_fd(int fd)
{
	_fd = fd;
}

int AReaderFileDescriptor::get_next_line(std::string & line)
{
	std::string	tmp	= std::string("");
	bool		run		= true;
	int			ret		= 1;
	size_t		p_oel;

	line = "";
	while (run)
	{
		tmp += _buffer;
		p_oel = tmp.find("\r\n");

		if (ret == 0)
		{
			line = tmp;
			run = false;
		}
		else if (p_oel == std::string::npos)
		{
			ret = _read();
			if (ret == -1)
				return (ret);
			_buffer[ret] = 0;
		}
		else
		{
			line = tmp.substr(0, p_oel);
			run = false;
		}
	}

	if (tmp.length() > p_oel) //Handle p_oel == std::string::npos (size_t MAX)
	{
		tmp.copy(_buffer, tmp.length() - p_oel - 2, p_oel + 2);
		_buffer[tmp.length() - p_oel - 2] = 0;
	}
	// std::cout << "##LINE : " << line << std::endl;
	// std::cout << "##BUFF : " << _buffer << std::endl;
	return (ret);
}

void
AReaderFileDescriptor::read_body(std::string & line, int content_length)
{
	line = _buffer;
	_buffer[0] = 0;
	char buffer[content_length + 1];
	int ret = recv(_fd, buffer, content_length, MSG_DONTWAIT);
	buffer[ret] = 0;
	line = line + buffer;
	std::cout << "body: " << line << std::endl;
}

void
AReaderFileDescriptor::read_until_end(std::string & line)
{
	get_next_line(line);

//	std::cout << "temp: " << temp << std::endl;
}

std::string
AReaderFileDescriptor::get_next_buffer(void)
{
	_read();
	return (get_buffer());
}

void
AReaderFileDescriptor::write_body(int fd)
{
	int n_read = 0;

	write(fd, _buffer, std::strlen(_buffer));
	while ((n_read = _read()) > 0){
		std::cout << "## (" << n_read << ") " << _buffer << std::endl;
		write (fd, _buffer, n_read);
	}
	dup2(_fd, fd);
}