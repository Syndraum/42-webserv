/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerResponseCGI.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 16:19:20 by cdai              #+#    #+#             */
/*   Updated: 2021/11/16 17:10:49 by mchardin         ###   ########.fr       */
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
	std::string		line;
	int				gnl_ret = 1;
	
	_builder.set_message(_response);
	while (gnl_ret && (gnl_ret = _reader.get_next_line(line)))
	{
		if (gnl_ret == -1)
			return ;
		line += "\r";
		try
		{
			_builder._parse_headers(line);
		}
		catch (std::exception& e)
		{
			try
			{
				ExitException	&e_exit = dynamic_cast<ExitException&>(e);
				(void)e_exit;
				throw (ExitException());
			}
			catch (std::bad_cast &bc)
			{
				_reader._reset_buffer();
				throw e;
			}
		}
		if (_response->get_header_lock())
		{
			if (!_response->has_header("Content-Length"))
			{
				_reader.read_until_end(line);
				_response->set_body(line);
			}
			else
			{
				_reader.read_body(line, std::atoi(_response->get_header("Content-Length").c_str()));
				_response->set_body(line);
			}
			_response->set_body_lock(true);
//			get_client_socket().get_reader()._reset_buffer();
			gnl_ret = 0;
		}
	}
}
