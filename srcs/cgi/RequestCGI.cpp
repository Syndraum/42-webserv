/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestCGI.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:14:02 by cdai              #+#    #+#             */
/*   Updated: 2021/11/14 21:32:16 by syndraum         ###   ########.fr       */
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
