/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_to_test_request.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:58:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/24 22:58:23 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Core.hpp"
#include "Server.hpp"

int		main()
{
	Core core = Core();
	core.addServer();
	core.getServer()
		.addPort(8888)
		.addPort(3333)
		;
	core.start();
//maia's part
// #include "includes.hpp"
// #include "BuilderRequest.hpp"

// std::string	error_msg(int code) // ADD TO RESPONSE
// {
// 	if (code == BAD_REQUEST)
// 		return ("Bad Request");
// 	else if(code == BAD_VERSION)
// 		return ("HTTP Version Not Supported");
// 	else if(code == NOT_IMPLEMENTED)
// 		return("Not Implemented");
// 	return (0);
// }

// int		print_error(int code) // ADD TO RESPONSE
// {
// 	std::cout << code << " " << error_msg(code) << std::endl;
// 	return(code);
// }

// int		main() // run with "cat test_request | ./webserv"
// {
// 	BuilderRequest bd;
// 	Request	*	request = 0;
// 	// int			code;

// 	try
// 	{	
// 		bd.parse_request(std::cin);
// 		request = bd.get_request();
// 		bd.reset();
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}
// 	// code = parse_request(std::cin, &request);
// 	// if (code != OK)
// 	// 	return(print_error(code));
// 	if (request)
// 		request->print_debug();
// 	delete request;
}
