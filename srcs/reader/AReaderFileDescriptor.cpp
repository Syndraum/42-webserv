/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AReaderFileDescriptor.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:22:22 by cdai              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/16 21:34:20 by mchardin         ###   ########.fr       */
=======
/*   Updated: 2021/11/18 02:42:18 by syndraum         ###   ########.fr       */
>>>>>>> 59e4b0e0fa131b37b3aa51d8d6f7cd7b3b25ecfb
/*                                                                            */
/* ************************************************************************** */

#include "AReaderFileDescriptor.hpp"

AReaderFileDescriptor::AReaderFileDescriptor(void)
{}

AReaderFileDescriptor::AReaderFileDescriptor(int fd):
_fd(fd),
_size(0),
_chunck()
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
	if (this != &rhs)
	{
		_fd = rhs._fd;
		for (int i = 0; i < BUFFER_SIZE; i++)
			_buffer[i] = rhs._buffer[i];
		_size = rhs._size;
		_chunck = rhs._chunck;
	}
	return *this;
}

void
AReaderFileDescriptor::_reset_buffer(void)
{
	for (int i = 0; i < BUFFER_SIZE; i++)
		_buffer[i] = '\0';
	_size = 0;
}

std::string
AReaderFileDescriptor::get_buffer(void) const
{
	std::string tmp = std::string(_buffer, _size);
	std::cout << "size : " << tmp.size() << std::endl;
	return (tmp);
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
	std::string	tmp		= std::string("");
	bool		run		= true;
	int			ret		= 1;
	size_t		p_eol;

	line = "";
	while (run)
	{
		tmp += std::string(_buffer, _size);
		p_eol = tmp.find("\r\n");

		if (ret == 0)
		{
			line = tmp;
			run = false;
		}
		else if (p_eol == std::string::npos)
		{
			ret = next_read();
			if (ret == -1){
				_reset_buffer();
				return (ret);
			}
			_buffer[ret] = 0;
		}
		else
		{
			line = tmp.substr(0, p_eol);
			run = false;
		}
	}

	if (tmp.length() > p_eol) //Handle p_eol == std::string::npos (size_t MAX)
	{
		tmp.copy(_buffer, tmp.length() - p_eol - 2, p_eol + 2);
		_buffer[tmp.length() - p_eol - 2] = 0;
		_size = tmp.length() - p_eol - 2;
	}
	return (ret);
}

void
AReaderFileDescriptor::read_body(std::string & line, int content_length)
{
	line = _buffer;
	_buffer[0] = 0;
	char buffer[content_length + 1];
	int ret = recv(_fd, buffer, content_length, MSG_DONTWAIT);
	if (ret < 0)
		throw std::exception();
	buffer[ret] = 0;
	line = line + buffer;
	std::cout << "body: " << line << std::endl;
}

void
AReaderFileDescriptor::read_until_end(std::string & line)
{
	get_next_line(line);
}

int
AReaderFileDescriptor::next_read(size_t start)
{
	std::string	tmp;
	size_t		remain	= 0;
	int			ret		= 1;

	if (start > BUFFER_SIZE - 1)
		throw OutOfBuffer();
	if (start != BUFFER_SIZE - 1){
		if (start >= _size)
			throw OutOfBound();
		remain = _size - start;
		tmp = std::string(&_buffer[start], remain);
		tmp.copy(_buffer, remain);
		_buffer[remain] = 0;
	}
	ret = _read(&_buffer[remain], BUFFER_SIZE - 1 - remain);
	_size = remain;
	if (ret >= 0)
		_size += ret;
	return(ret);
}

int
AReaderFileDescriptor::fill_buffer()
{
	int ret = 0;

	if (_size >= BUFFER_SIZE - 1)
		return (-2);
	ret = _read(&_buffer[_size], BUFFER_SIZE - 1 - _size);
	if (ret <= -1)
		throw std::exception(); //
	else if (ret == 0)
		throw std::exception(); //
	if (ret >= 0)
		_size += ret;
	return (ret);
}

int
AReaderFileDescriptor::write_body(int fd)
{
	write (fd, _buffer, _size);
	return(next_read());
}

bool
AReaderFileDescriptor::has_line() const
{
	// std::cout << "BUFFER : " << _chunck << std::endl;
	if (_chunck.find("\r\n") == std::string::npos)
		return (false);
	return (true);
}



bool
AReaderFileDescriptor::has_all_headers() const
{
	// std::cout << "BUFFER : " << _chunck << std::endl;
	if (_chunck.find("\r\n\r\n") == std::string::npos)
		return (false);
	return (true);
}

void
AReaderFileDescriptor::concatenation()
{
	std::string tmp(_buffer, _size);

	_chunck = _chunck + tmp;
	// std::cout << "BUFFER : " << tmp << std::endl;
	// std::cout << "CHUNCK : " << _chunck << std::endl;
}

void
AReaderFileDescriptor::reset_chunck()
{
	_chunck = "";
}

void
AReaderFileDescriptor::cut_header()
{
	size_t		pos_buffer;
	size_t		pos_end_of_header;
	size_t		pivot;
	std::string	tmp;

	pos_buffer = _chunck.find(_buffer);
	if (pos_buffer == std::string::npos)
		return;
	pos_end_of_header = _chunck.find("\r\n\r\n") + 4;
	if (pos_end_of_header == std::string::npos)
		return;
	pivot = pos_end_of_header - pos_buffer;
	if (pivot != 0)
	{
		tmp = std::string(_buffer, _size);
		tmp.copy(_buffer, _size - pivot, pivot);
		_buffer[_size - pivot] = 0;
		_size = _size - pivot;

		// tmp = std::string(_buffer, _size);
		// std::cout << "Size : " << _size << " BUFFER : |" << _buffer << "|" << std::endl;
	}
}

void
AReaderFileDescriptor::move_buffer_until(size_t pos)
{
	std::string	tmp;
	size_t		remain	= 0;

	if (pos >= _size)
		throw OutOfBound();
	if (pos == 0)
		return ;
	remain = _size - pos;
	tmp = std::string(&_buffer[pos], remain);
	tmp.copy(_buffer, remain);
	_buffer[remain] = 0;
	_size = remain;
}

std::string &
AReaderFileDescriptor::get_chunck()
{
	return (_chunck);
}

void
AReaderFileDescriptor::debug() const
{
	std::cout << "Size : " << _size << " BUFFER : |" << _buffer << "|" << std::endl;
}
