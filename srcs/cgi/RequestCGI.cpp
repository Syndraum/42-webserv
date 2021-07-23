/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestCGI.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:14:02 by cdai              #+#    #+#             */
/*   Updated: 2021/07/14 15:37:24 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestCGI.hpp"

RequestCGI::RequestCGI(CGI & cgi):
_cgi(cgi)
{}

RequestCGI::~RequestCGI(void)
{}

RequestCGI const &
RequestCGI::operator=(RequestCGI const &rhs)
{
	_cgi = rhs._cgi;
	return (*this);
}

void RequestCGI::send(const std::string & script_path)
{
	_cgi.start(*this, script_path);
}
