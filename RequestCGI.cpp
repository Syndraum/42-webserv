/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestCGI.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:14:02 by cdai              #+#    #+#             */
/*   Updated: 2021/07/13 16:45:39 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestCGI.hpp"

// private
RequestCGI::RequestCGI(void):
_cgi(*(new CGI))
{}

RequestCGI::RequestCGI(CGI & cgi, std::map<std::string, std::string> & glov_env):
_env_cgi(glov_env),
_cgi(cgi)
{}

RequestCGI::~RequestCGI(void)
{}

RequestCGI const &
RequestCGI::operator=(RequestCGI const &rhs)
{
	_env_cgi = rhs.get_env_cgi();
	_cgi = rhs.get_CGI();
	_response = rhs.get_response();
	return (*this);
}

RequestCGI &
RequestCGI::add_env(std::string key, std::string value)
{
	_env_cgi.insert(std::pair<std::string, std::string>(key, value));
	return (*this);
}

std::map<std::string, std::string>
RequestCGI::get_env_cgi(void) const
{
	return (_env_cgi);
}

CGI &
RequestCGI::get_CGI(void) const
{
	return (_cgi);
}

Response
RequestCGI::get_response(void) const
{
	return (_response);
}
