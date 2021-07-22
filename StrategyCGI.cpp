/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyCGI.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 11:55:53 by cdai              #+#    #+#             */
/*   Updated: 2021/07/22 12:11:23 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StrategyCGI.hpp"

StrategyCGI::StrategyCGI(void){}

StrategyCGI::StrategyCGI(StrategyCGI const & src)
{
	*this = src;
}

StrategyCGI::~StrategyCGI(void)
{
	
}

StrategyCGI &	StrategyCGI::operator=(StrategyCGI const & rhs)
{
	if (this != &rhs)
		;
	return *this;
}

Response * 
StrategyCGI::create(Server & server, Request & request)
{
	(void)server;
	(void)request;

	Response * response = 0;

//	response = new Response();
//	request.set_path(server.get_full_path(request.get_path()));
//	request.action(*response);
	return (response);
}
