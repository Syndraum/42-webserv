/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyCGI.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 11:55:53 by cdai              #+#    #+#             */
/*   Updated: 2021/07/22 18:42:09 by cdai             ###   ########.fr       */
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

	Server::cgi_map::iterator it = server.get_cgi_map().find("." + Extension::get_extension(request.get_path()));

	std::cout << "it->second->get_exec_name() : " << it->second.get_exec_name() << std::endl;
	it->second.add_CGI_param("AUTH_TYPE", "");
	it->second.add_CGI_param("CONTENT_LENGTH", request.get_header("Content-Length"));
	it->second.add_CGI_param("CONTENT_TYPE", request.get_header("Content-Type"));
	it->second.add_CGI_param("GATEWAY_INTERFACE", "CGI/1.1");
	it->second.add_CGI_param("PATH_INFO", "");
	it->second.add_CGI_param("QUERY_STRING", request.get_body());
	it->second.add_CGI_param("REMOTE_ADDR", "127.0.0.1");
	
	it->second.add_CGI_param("REMOTE_USER", "");
	it->second.add_CGI_param("REQUEST_METHOD", request.get_method()->get_name());
	it->second.add_CGI_param("SCRIPT_NAME", it->second.get_exec_name());
	it->second.add_CGI_param("SERVER_NAME", "localhost");
	it->second.add_CGI_param("SERVER_PORT", "8081");
	it->second.add_CGI_param("SERVER_PROTOCOL", "HTTP/1.1");
	it->second.add_CGI_param("SERVER_SOFTWARE", "Webserviette/0.1");

	it->second.print();
	int fd = it->second.start();
	std::cout << "fd : " << fd << std::endl;

	Response * response = 0;
	
	response = new Response();
//	request.set_path(server.get_full_path(request.get_path()));
//	request.action(*response);
	return (response);
}
