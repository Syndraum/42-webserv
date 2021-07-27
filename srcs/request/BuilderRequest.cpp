/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuilderRequest.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:49:15 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/20 17:08:01 by cdai             ###   ########.fr       */
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

}

int
BuilderRequest::_add_method(std::string line)
{
	int ret = line.find(' ');

	std::string name = line.substr(0, ret);
	_request->set_method(_methods->get_method( name));
	if (!_request->get_method())
		throw MethodNotImplemented();
	return (ret + 1);
}

int
BuilderRequest::_add_path(std::string line)
{
	size_t		len = line.find(' ');
	std::string	tmp;
  
	if (len == std::string::npos)
		throw BadRequest();
	tmp = line.substr(0, len);
	_request->set_uri(tmp);
	_request->set_path(_request->get_uri().get_path());
	return(len + 1);
}

int
BuilderRequest::_add_version(std::string line)
{
	if (line.compare(0, 8, Info::http_revision))
		throw BadHttpVersion();
	_request->set_version(Info::http_revision);
	return (8);
}

void
BuilderRequest::_first_line(std::string line)
{
	int j = 0;


	if (line[0] == '\0')
		throw BadRequest();
	j = _add_method(line);
	j += _add_path(&line[j]);
	j += _add_version(&line[j]);
	if (line[j] != '\r')
		throw BadRequest();
}

// void
// BuilderRequest::_parse_headers(std::string line)
// {
// 	size_t		len = line.find(": ");

// 	if (line.length() == 1 && line[0] == '\r'){
// 		_request->set_header_lock(true);
// 		// _request->set_body_lock(true); // TEMPORARY
// 	}
// 	else if (line[line.length() - 1] != '\r' || len == std::string::npos || line[len - 1] == ' ')
// 		throw BadRequest();
// 	_request->add_header(line.substr(0, len), line.substr(len + 2, line.length() - len - 3));
// }

void
BuilderRequest::parse_request(std::string & line)
{
	if (is_first_line())
		_first_line(line);
	else if (!(_message->get_header_lock()))
		_parse_headers(line);
}

// Request *
// BuilderRequest::get_request() const
// {
// 	return _request;
// }

void
BuilderRequest::set_message(Message * message)
{
	BuilderMessage::set_message(message);
	_request = reinterpret_cast<Request *>(message);
	if (!_request)
		throw std::exception();
}

void
BuilderRequest::set_library(MethodLibrary * library)
{
	if (!library)
		throw std::exception();
	_methods = library;
}

bool
BuilderRequest::is_first_line() const
{
	if (_request->get_method() == 0)
		return true;
	if (_request->get_path() == "")
		return true;
	if (_request->get_version() == "")
		return true;
	return false;
}
