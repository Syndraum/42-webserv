/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerResponseCGI.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 16:19:20 by cdai              #+#    #+#             */
/*   Updated: 2021/07/26 13:00:11 by cdai             ###   ########.fr       */
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
		// std::cout << "CGI line: " << line << std::endl;
		line += "\r";
		_builder._parse_headers(line);
		if (_response->get_header_lock())
		{
			if (!_response->has_header("Content-Length"))
			{
				std::cout << "No Content-Length" << std::endl;
				_reader.read_until_end(line);
				_response->set_body(line);
			}
			else
			{
				std::cout << "Content-Length : " << _response->get_header("Content-Length") << std::endl;

				_reader.read_body(line, std::atoi(_response->get_header("Content-Length").c_str()));
				_response->set_body(line);
			}
			_response->set_body_lock(true);
//			get_client_socket().get_reader()._reset_buffer();
			gnl_ret = 0;
		}
	}
}
