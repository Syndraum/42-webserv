/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_request.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:58:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/23 12:53:33 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

using namespace std;

string	error_msg(int code) // ADD TO RESPONSE
{
	if (code == BAD_REQUEST)
		return ("Bad Request");
	else if(code == BAD_VERSION)
		return ("HTTP Version Not Supported");
	else if(code == NOT_IMPLEMENTED)
		return("Not Implemented");
	return (0);
}

int		print_error(int code) // ADD TO RESPONSE
{
	cout << code << " " << error_msg(code) << endl;
	return(code);
}

int		main() // run with "cat test_request | ./webserv"
{
	Request		request;
	int			code;

	code = parse_request(cin, &request);
	if (code != OK)
		return(print_error(code));
	request.print_debug();
}
