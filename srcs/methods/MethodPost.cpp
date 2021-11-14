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
AMethod("POST"),
_uploader(Upload())
{}

MethodPost::~MethodPost() {}

void
MethodPost::action(const Request & request, Response & response, Server & server, AReaderFileDescriptor & reader)
{
	Extension *	extension	= Extension::get_instance();
	std::string ext			= Extension::get_extension(request.get_path().c_str());
	std::string mine		= extension->get_reader()[ext];
	// Upload		uploader	= Upload(reader);

	if (has_upload(request))
	{
		_uploader.set_reader(reader)->upload(server, request);
		// uploader.upload(server, request);
	}

	if (mine.empty())
		mine = "application/octet-stream";
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

AMethod *
MethodPost::clone() const
{
	AMethod * clone = new MethodPost();
	*clone = *this;
	return (clone);
}

bool
MethodPost::has_upload(const Request & request)
{
	bool	has_header	= request.has_header("Content-Type");
	size_t	position;

	if (!has_header)
		return (false);
	position = request.get_header("Content-Type").find("multipart/form-data", 0);
	return (position != std::string::npos);
}