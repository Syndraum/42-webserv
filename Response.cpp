/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:02:30 by syndraum          #+#    #+#             */
/*   Updated: 2021/06/18 15:45:01 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(int code) : _version("HTTP/1.1"), _code(code), _body("")
{

}

Response::Response(Response const & src)
{
	*this = src;
}

Response::~Response(void)
{
	
}

Response &	Response::operator=(Response const & rhs)
{
	if (&rhs != this){
		this->_version = rhs._version;
		this->_code = rhs._code;
		this->_headers = rhs._headers;
		this->_body = rhs._body;
	}
	return *this;
}

Response & Response::addHeader(std::string name, std::string content)
{
	_headers.insert(std::pair<std::string, std::string>(name, content));
	return *this;
}

std::string	Response::getResponse()
{
	std::stringstream ss;

	ss << _version << " " << _code << " " << "OK" << "\r\n";
	for (header_map::iterator it = _headers.begin(); it != _headers.end(); it++)
	{
		ss << it->first << ": " << it->second << "\r\n";
	}
	ss << "\r\n\r\n";
	if (_body != "")
		ss << _body;
	return ss.str();
}

void	Response::sendResponse(int fd)
{
	std::string response = getResponse();

	write(fd, response.data(), response.size());
}

