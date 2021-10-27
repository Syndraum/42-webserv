/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodPost.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:05:23 by cdai              #+#    #+#             */
/*   Updated: 2021/07/20 16:44:19 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MethodPost.hpp"

MethodPost::MethodPost(void) :
AMethod("POST")
{}

MethodPost::~MethodPost() {}

void
MethodPost::action(const Request & request, Response & response, Server & server, AReaderFileDescriptor & reader)
{
	(void)response;
	Extension * extension = Extension::get_instance();
	std::string ext = Extension::get_extension(request.get_path().c_str());
	std::string mine = extension->get_reader()[ext];
	if (request.has_header("Content-Type") && request.get_header("Content-Type").find("multipart/form-data", 0) != std::string::npos)
	{
		upload(request, server, reader);
	}

	if (mine.empty())
		mine = "application/octet-stream";
	// std::cout << "ext : " << ext << std::endl;
	try
	{
		response
			.set_code(200)
			.set_body_from_file(request.get_path().c_str())
			.add_header(
				"Content-type", 
				mine
				)
			;
	}
	catch(const std::exception& e)
	{
		response.set_error(404, server.get_path_error_page());
	}
}

std::string
MethodPost::get_boundary(const Request & request)
{
	std::string	content_type	= request.get_header("Content-type");
	std::string	boundary;
	size_t		p_bound			= content_type.find("boundary");
	size_t		p_egal;

	if (p_bound != std::string::npos)
	{
		p_egal = content_type.find('=', p_bound);

		boundary = content_type.substr(p_egal);
		std::cout << "boundary : " << boundary << std::endl;
	}
	return (boundary);
}

void
MethodPost::upload(const Request & request, Server & server, AReaderFileDescriptor & reader)
{
	std::string	boundary	= get_boundary(request);
	std::string	chuck = reader.get_buffer();

	reader._read();
	chuck += reader.get_buffer();
	(void)server;
}
