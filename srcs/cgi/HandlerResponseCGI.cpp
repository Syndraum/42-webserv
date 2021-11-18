/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerResponseCGI.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 16:19:20 by cdai              #+#    #+#             */
/*   Updated: 2021/11/18 23:26:29 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandlerResponseCGI.hpp"

HandlerResponseCGI::HandlerResponseCGI(void):
_reader(1),
_builder(),
_response(0)
{}

HandlerResponseCGI::HandlerResponseCGI(int fd):
_reader(fd),
_builder(),
_response(0)
{}

HandlerResponseCGI::HandlerResponseCGI(HandlerResponseCGI const & rhs):
_reader(1)
{
	*this = rhs;
}

HandlerResponseCGI::~HandlerResponseCGI(void)
{}

HandlerResponseCGI & 
HandlerResponseCGI::operator=(HandlerResponseCGI const & rhs)
{
	if (this != &rhs)
	{
		_reader = rhs._reader;
		_builder = rhs._builder;
		_response = rhs._response;
	}
	return (*this);
}

void
HandlerResponseCGI::set_fd(int fd)
{
	_reader.set_fd(fd);
}

Message *
HandlerResponseCGI::get_response()
{
	return (_response);
}

void
HandlerResponseCGI::init()
{
	_response = new Message();
}

void
HandlerResponseCGI::clear()
{
	delete _response;
}

void 
HandlerResponseCGI::parse()
{
	std::string				line = "";
	std::string &			chunck	= _reader.get_chunck();
	int						ret		= 0;
	
	_builder.set_message(_response);
	if (!_response->get_header_lock())
	{
		if (_reader.has_all_headers())
		{
			_reader.cut_header();
			while (chunck.find("\r\n\r\n") != std::string::npos)
			{
				line = chunck.substr(0, chunck.find("\r\n")) + "\r";
				_builder._parse_headers(line);
				chunck = chunck.substr(chunck.find("\r\n") + 2);
			}
			_response->set_header_lock(true);
			_reader.debug();
		}
		else
		{
			ret = _reader.next_read();
			_reader.concatenation();
		}
	}
	else
	{
		_response->set_body(_response->get_body() + _reader.get_buffer());
		try
		{
			ret = _reader.next_read();
		}
		catch(const AReaderFileDescriptor::EndOfFile& e)
		{
			_response->set_body_lock(true);
		}
	}
}
