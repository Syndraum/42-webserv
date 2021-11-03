/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodPost.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:05:23 by cdai              #+#    #+#             */
/*   Updated: 2021/11/03 16:37:05 by syndraum         ###   ########.fr       */
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
	Extension *	extension	= Extension::get_instance();
	std::string ext			= Extension::get_extension(request.get_path().c_str());
	std::string mine		= extension->get_reader()[ext];
	Upload		uploader	= Upload(reader);

	if (request.has_header("Content-Type") && request.get_header("Content-Type").find("multipart/form-data", 0) != std::string::npos)
	{
		uploader.upload(server, request);
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
	(void)response;
}

// std::string
// MethodPost::get_boundary(const Request & request)
// {
// 	std::string	content_type	= request.get_header("Content-type");
// 	std::string	boundary;
// 	size_t		p_bound			= content_type.find("boundary");
// 	size_t		p_egal;

// 	if (p_bound != std::string::npos)
// 	{
// 		p_egal = content_type.find('=', p_bound);
// 		boundary = content_type.substr(p_egal);
// 	}
// 	return (boundary);
// }

// void
// MethodPost::upload(const Request & request, Server & server, AReaderFileDescriptor & reader)
// {
// 	bool		process		= false;
// 	std::string	boundary	= "--" + get_boundary(request);
// 	std::string	buffer		= reader.get_buffer();
// 	std::string next_buffer;
// 	std::string	chunck;
// 	size_t		pos;

// 	buffer += reader.get_next_buffer();
// 	next_buffer = reader.get_next_buffer();
// 	chunck = buffer + next_buffer;
// 	if ((pos = chunck.find(boundary)) != std::string::npos)
// 	{

// 	}
// 	(void)server;
// }

// int
