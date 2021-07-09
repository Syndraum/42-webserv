/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:02:30 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/02 15:41:38 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(Request & request, int code) :
_version("HTTP/1.1"),
_code(code),
_body(""),
_request(request)
{}

Response::Response(Response const & src) : _request(src._request)
{
	*this = src;
}

Response::~Response(void)
{
	
}

Response &
Response::operator=(Response const & rhs)
{
	if (&rhs != this){
		this->_version = rhs._version;
		this->_code = rhs._code;
		this->_headers = rhs._headers;
		this->_body = rhs._body;
		this->_request = rhs._request;
	}
	return *this;
}

Response &
Response::add_header(std::string name, std::string content)
{
	_headers.insert(std::pair<std::string, std::string>(name, content));
	return *this;
}

void
Response::clear_header()
{
	_headers.clear();
}

std::string
Response::get_response()
{
	std::stringstream ss;

	ss << _version << " " << _code << " " << get_message(_code) << "\r\n";
	add_header("Content-Length", _body.length());
	for (header_map::iterator it = _headers.begin(); it != _headers.end(); it++)
	{
		ss << it->first << ": " << it->second << "\r\n";
	}
	ss << "\r\n";
	ss << _body;
	return ss.str();
}

void
Response::send_response(int fd)
{
	std::string response = get_response();

	write(fd, response.data(), response.size());
	_request.reset();
}

std::string
Response::get_message(int code)
{
	if (code >= 500)
		return (_5xx__response(code));
	else if (code >= 400)
		return (_4xx__response(code));
	else if (code >= 300)
		return (_3xx__response(code));
	else if (code >= 200)
		return (_2xx__response(code));
	else if (code >= 100)
		return (_1xx__response(code));
	else
		throw std::exception();
}

Response &
Response::set_code(int code)
{
	_code = code;
	return *this;
}

//cdai set_body
Response &
Response::set_body_from_file(const std::string & filename)
{
	Reader	file_reader(filename);
	file_reader.open();
	file_reader.to_string(_body);
	file_reader.close();
	return *this;
}

Response &
Response::set_body(const std::string & body)
{
	_body = body;
	return *this;
}

Response &
Response::set_404(std::string & filename)
{
	_code = 404;
	return set_body_from_file(filename);
}

std::string
Response::_1xx__response(int code)
{
	switch (code)
	{
	case 100:
		return ("Continue");
	case 101:
		return ("Switching Protocols");
	case 102:
		return ("Processing");
	case 103:
		return ("Early Hints");
	default:
		throw std::exception();
		break;
	}
}

std::string
Response::_2xx__response(int code)
{
	switch (code)
	{
	case 200:
		return ("OK");
	case 201:
		return ("Created");
	case 202:
		return ("Accepted");
	case 203:
		return ("No Content");
	case 204:
		return ("Reset Content");
	case 205:
		return ("Non-Authoritative Information");
	case 206:
		return ("Non-Authoritative Information");
	default:
		throw std::exception();
		break;
	}
}

std::string
Response::_3xx__response(int code)
{
	switch (code)
	{
	case 300:
		return ("Multiple Choices");
	case 301:
		return ("Moved Permanently");
	case 302:
		return ("Found");
	case 303:
		return ("See Other");
	case 304:
		return ("Not Modified");
	case 305:
		return ("Use Proxy");
	case 306:
		return ("Switch Proxy");
	case 307:
		return ("Temporary Redirect");
	case 308:
		return ("Permanent Redirect");
	case 310:
		return ("Too many Redirects");
	default:
		throw std::exception();
		break;
	}
}

std::string
Response::_4xx__response(int code)
{
	switch (code)
	{
	case 400:
		return ("Bad Request");
	case 401:
		return ("Unauthorized");
	case 402:
		return ("Payment Required");
	case 403:
		return ("Forbidden");
	case 404:
		return ("Not Found");
	case 405:
		return ("Method Not Allowed");
	case 406:
		return ("Not Acceptable");
	case 407:
		return ("Proxy Authentication Required");
	case 408:
		return ("Request Time-out");
	case 409:
		return ("Conflict");
	case 410:
		return ("Gone");
	case 411:
		return ("Length Required");
	case 412:
		return ("Precondition Failed");
	case 413:
		return ("Request Entity Too Large");
	case 414:
		return ("Request-URI Too Long");
	case 415:
		return ("Unsupported Media Type");
	case 416:
		return ("Requested range unsatisfiable");
	case 417:
		return ("Expectation failed");
	case 418:
		return ("I’m a teapot");
	case 421:
		return ("Bad mapping");
	default:
		throw std::exception();
		break;
	}
}

std::string
Response::_5xx__response(int code)
{
	switch (code)
	{
	case 500:
		return ("Internal Server Error");
	case 501:
		return ("Not Implemented");
	case 502:
		return ("Bad Gateway ou Proxy Error");
	case 503:
		return ("Service Unavailable");
	case 504:
		return ("Gateway Time-out");
	case 505:
		return ("HTTP Version not supported");
	case 506:
		return ("Variant Also Negotiates");
	case 507:
		return ("Insufficient storage");
	case 508:
		return ("Loop detected");
	case 509:
		return ("Bandwidth Limit Exceeded");
	case 510:
		return ("Not extended");
	default:
		throw std::exception();
		break;
	}
}
