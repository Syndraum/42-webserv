/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:58:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/02 15:50:10 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"
#include "BuilderCore.hpp"
#include "Reader.hpp"

int		main(int argc, char *argv[])
{
	std::string path_config_file = "default.conf";

	if (argc > 2)
	{
		std::cerr << "Error: too much arguemnt" <<std::endl;
		return (2);
	}
	if (argc == 2)
		path_config_file = argv[1];
	Reader reader(path_config_file);
	reader.open();
	if (reader.get_ifs().fail())
	{
		std::cerr << "Error: Configuration file: " << path_config_file << " not found" << std::endl;
		return (1);
	}
	Core core = Core();
	BuilderCore builder_core(reader.get_ifs(), &core);
	builder_core.print_debug();
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
