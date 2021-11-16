/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodGet.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:20 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/16 13:30:28 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MethodGet.hpp"

MethodGet::MethodGet(void) :
AMethod("GET")
{}

MethodGet::~MethodGet()
{}

void
MethodGet::action(const Request & request, Response & response, Server & server, AReaderFileDescriptor & reader)
{	
	Extension *	extension = Extension::get_instance();
	std::string	ext = Extension::get_extension(request.get_path().c_str());
	std::string	mine = extension->get_reader()[ext];
	(void)reader;

	if (mine.empty())
		mine = "application/octet-stream";
	try
	{
		response
			.set_code(200)
			.set_filename(request.get_path())
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
	finished();
}

AMethod *
MethodGet::clone() const
{
	AMethod * clone = new MethodGet();
	*clone = *this;
	return (clone);
}
