/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:02:30 by syndraum          #+#    #+#             */
/*   Updated: 2021/11/19 21:20:46 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(int code) :
Message(),
_version(Info::http_revision),
_code(code),
_state(WRITE_HEADER),
_file_reader()
{}

Response::Response(Response const & src)
{
	*this = src;
}

Response::~Response(void)
{}

Response &
Response::operator=(Response const & rhs)
{
	if (&rhs != this){
		this->_version = rhs._version;
		this->_code = rhs._code;
		this->_headers = rhs._headers;
		this->_body = rhs._body;
		this->_state = rhs._state;
		this->_file_reader = rhs._file_reader;
	}
	return *this;
}

std::string
Response::get_header()
{
	std::stringstream ss;

	ss << _version << " " << _code << " " << get_message(_code) << "\r\n";
	if (_body.empty())
		add_header("Content-Length", _file_reader.get_length());
	else
		add_header("Content-Length", _body.size());
	add_header("Server", Info::server_name + "/" + Info::version );
	for (header_map::iterator it = _headers.begin(); it != _headers.end(); it++)
	{
		ss << it->first << ": " << it->second << "\r\n";
	}
	ss << "\r\n";
	return ss.str();
}

std::string
Response::get_response()
{
	if (!_body.empty())
	{
		return _body;
	}
	return _file_reader.get_buffer();
}

void
Response::send_header(int fd)
{
	std::string response = get_header();
	ssize_t		ret;

	if (response.size())
	{
		ret = send(fd, response.data(), response.size(), 0);
		if (ret < (ssize_t)0)
			throw (std::exception());
		else if ((size_t)ret < response.size())
			_body = response.substr((size_t)ret, response.size() - ret);
	}
	_state = Response::WRITE_BODY;
}

void
Response::send_body(int fd)
{
	std::string	response = get_response();
	ssize_t		ret;
	if (response.size())
	{
		ret = send(fd, response.data(), response.size(), MSG_NOSIGNAL);
		if (ret < (ssize_t)0)
			throw (std::exception());
		else if ((size_t)ret < response.size())
			_body = response.substr((size_t)ret, response.size() - ret);
		else if (_file_reader.finished() || !_body.empty())
		{
			_file_reader.close();
			_state = Response::END;
		}
	}
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

Response &
Response::set_filename(const std::string & filename)
{
	_file_reader.get_ifs().open(filename.c_str(), std::ios_base::in );
	if (_file_reader.get_ifs().fail())
		throw std::exception();
	_file_reader.set_length();
	return *this;
}

Response &
Response::set_error(int code, std::string const & path_error_file)
{
	Reader			file_reader(path_error_file);
	StringPP		m_template;
	
	try
	{
		file_reader.open();
		file_reader.to_string(m_template.str());
		m_template.replace_all("{{CODE}}", code);
		m_template.replace_all("{{MESSAGE}}", get_message(code));
		m_template.replace_all("{{SERVER_NAME}}", Info::server_name);
		m_template.replace_all("{{VERSION}}", Info::version);
		this->set_code(code)
			.set_body(m_template.str())
			.clear_header()
			.add_header("Content-Type", "text/html");
	}
	catch (std::exception &e)
	{
		this->set_code(code).clear_header();
	}
	file_reader.close();
	return *this;
}

int
Response::get_code() const
{
	return (_code);
}

Response::response_state
Response::get_state() const
{
	return (_state);
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
