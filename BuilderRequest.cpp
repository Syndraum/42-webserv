/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuilderRequest.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:49:15 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/13 14:17:49 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BuilderRequest.hpp"

BuilderRequest::BuilderRequest(void) :
_request(0),
_methods(0)
{}

BuilderRequest::BuilderRequest(MethodLibrary * methods) :
_request(0),
_methods(methods)
{}

BuilderRequest::~BuilderRequest(void)
{
	delete _request;
}

int
BuilderRequest::add_method(std::string line)
{
	int ret = line.find(' ');
//	std::cout << "ret: " << ret << std::endl;
	std::string name = line.substr(0, ret);

//	std::cout << "name: " << name << std::endl;
	_request->set_method(_methods->get_method( name));
	if (!_request->get_method())
		throw MethodNotImplemented();
	return (ret + 1);
}

int
BuilderRequest::add_path(std::string line)
{
	size_t		len = line.find(' ');
	if (len == std::string::npos)
		throw BadRequest();
	_request->set_path(line.substr(0, len));
	// check characters
	return(len + 1);
}

int
BuilderRequest::add_version(std::string line)
{
	if (line.compare(0, 8, VERSION))
		throw BadHttpVersion();
	_request->set_version(VERSION);
	return (8);
}

void
BuilderRequest::first_line(std::string line)
{
	_request->set_first_line(false);
	if (line[0] == '\0')
		throw BadRequest();
	int	j = add_method(line);
	j += add_path(&line[j]);
	j += add_version(&line[j]);
	if (line[j] != '\r')
		throw BadRequest();
}

bool
BuilderRequest::parse_headers(std::string line)
{
	size_t		len = line.find(": ");

	if (line.length() == 1 && line[0] == '\r')
		return false;
	if (line[line.length() - 1] != '\r' || len == std::string::npos || line[len - 1] == ' ')
		throw BadRequest();
	_request->add_header(std::pair<std::string, std::string>(line.substr(0, len), line.substr(len + 2, line.length() - len - 3)));
	return (true);
}

void
BuilderRequest::parse_request(ASocket & socket)
{
	std::string		line;
	// bool			is_first_line = true;
	int				gnl_ret = 1;

	while( gnl_ret && (gnl_ret = socket.get_next_line(line)))
	{
		if (gnl_ret == -1)
			throw NoRequest();
//		std::cout << "gnl_ret: " << gnl_ret << std::endl;
		std::cout << "line: " << line << std::endl;

		line += "\r"; // Maybe, we can remote this line ? (from cdai)
		//check printable characters
		if (_request->get_first_line())
		{
			first_line(line);
		}
		else{
			std::cout << "this isn't the first line" << std::endl;
			if (!parse_headers(line))
			{
				socket.reset_buffer();
				gnl_ret = 0;
			}
		}
	}
}

Request *
BuilderRequest::get_request() const
{
	return _request;
}

void
BuilderRequest::set_request(Request * request)
{
	if (!request)
		throw std::exception();
	_request = request;
}

void
BuilderRequest::set_library(MethodLibrary * library)
{
	if (!library)
		throw std::exception();
	_methods = library;
}
