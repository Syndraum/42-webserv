/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerResponseCGI.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 16:19:20 by cdai              #+#    #+#             */
/*   Updated: 2021/07/25 18:10:28 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandlerResponseCGI.hpp"

HandlerResponseCGI::HandlerResponseCGI(void):
_reader(1)
{}

HandlerResponseCGI::HandlerResponseCGI(int fd):
_reader(fd)
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
		_response = rhs._response;
	}
	return (*this);
}

void 
HandlerResponseCGI::parse()
{
	std::string		line;
	int				gnl_ret = 1;
	
//	_builder.set_request(&get_request());
	while (gnl_ret && (gnl_ret = _reader.get_next_line(line)))
	{
		if (gnl_ret == -1)
			return ;
		std::cout << "line: " << line << std::endl;
		line += "\r";
		_parse_headers(line);
		if (_response->get_header_lock())
		{
			if (_response->get_header("Content-Length") == "")
			{
				std::cout << "No Content-Length" << std::endl;
				_reader.read_until_end();
				//std::cout << "_buffer: " << _buffer << std::endl;
				_response->set_body(line);
				_response->add_header("Content-Length", line.size());
			}
			else
			{
				std::cout << "Content-Length : " << _response->get_header("Content-Length") << std::endl;

				_reader.read_body(line, std::atoi(_response->get_header("Content-Length").c_str()));
				_response->set_body(line);
				_response->add_header("Content-Length", line.size());
			}
			_response->set_body_lock(true);
//			get_client_socket().get_reader()._reset_buffer();
			gnl_ret = 0;
		}
	}
}

void
HandlerResponseCGI::_parse_headers(std::string line)
{
	size_t		len = line.find(": ");

	if (line.length() == 1 && line[0] == '\r'){
		_response->set_header_lock(true);
//		_request->set_body_lock(true); // TEMPORARY
	}
	else if (line[line.length() - 1] != '\r' || len == std::string::npos || line[len - 1] == ' ')
		std::cerr << "error" << std::endl;
//		throw BadRequest();
	_response->add_header(line.substr(0, len), line.substr(len + 2, line.length() - len - 3));
}

void
HandlerResponseCGI::set_response(Response * response)
{
	_response = response;
}
