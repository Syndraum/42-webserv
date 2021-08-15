/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodGet.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:20 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:50:21 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MethodGet.hpp"

MethodGet::MethodGet(void) :
AMethod("GET")
{}

MethodGet::~MethodGet()
{}

void
MethodGet::action(const Request & request, Response & response, Server & server)
{	
	Extension * extension = Extension::get_instance();
	std::string ext = Extension::get_extension(request.get_path().c_str());
	std::string mine = extension->get_reader()[ext];

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
