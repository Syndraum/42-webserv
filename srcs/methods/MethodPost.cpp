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
MethodPost::action(const Request & request, Response & response)
{
	(void)request;
	(void)response;
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
		response.set_error(404);
	}
}
