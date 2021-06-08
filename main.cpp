/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:58:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/08 18:25:52 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define GET 0
#define POST 1
#define DELETE 2

#define VERSION "HTTP/1.1"

#define OK 200
#define BAD_REQUEST 400
#define BAD_VERSION 505
#define NOT_IMPLEMENTED 501

class Request
{
private:
	int		method;
	string	path;
	string	version;
	int		response_code;

	string	error_msg(int code);
	int		return_error(string msg);
	int		set_method(string line);
	int		set_path(string line);
	int		set_version(string line);
	int		first_line(string line);
	int		parse_headers(string line);
	/* data */
public:
	Request(/* args */);
	~Request();

	int		parsing();
	void	print_debug();
};

Request::Request() : response_code(200)
{}

Request::~Request()
{}

void	Request::print_debug()
{
	cerr << "METHOD CODE : " << method << " PATH : \"" << path << "\"";
}

string	Request::error_msg(int code)
{
	if (code == BAD_REQUEST)
		return ("Bad Request");
	else if(code == BAD_VERSION)
		return ("HTTP Version Not Supported");
	else if(code == NOT_IMPLEMENTED)
		return("Not Implemented");
	return (0);
}

int		Request::return_error(string msg)
{
	cout << response_code << " " << error_msg(response_code) << " : " << msg << endl;
	return(response_code);
}

int		Request::set_method(string line)
{
	if (!line.compare(0, 4, "GET "))
	{
		method = GET;
		return (4);
	}
	else if (!line.compare(0, 5, "POST "))
	{
		method = POST;
		return (5);
	}
	else if (!line.compare(0, 7, "DELETE "))
	{
		method = DELETE;
		return (7);
	}
	else
	{
		response_code = NOT_IMPLEMENTED;
		return (-1);
	}
}

int		Request::set_path(string line)
{
	size_t		len = line.find(' ');
	if (len == string::npos)
	{
		response_code = BAD_REQUEST;
		return(-1);
	}
	path = line.substr(0, len);
	// check characters
	return(len + 1);
}

int		Request::set_version(string line)
{
	if (line.compare(0, 8, VERSION))
	{
		response_code = BAD_VERSION;
		return (-1);
	}
	version = VERSION;
	return (8);
}

int		Request::first_line(string line)
{
	int	j = set_method(line);
	if (j < 0)
		return (return_error("wrong method"));
	j += set_path(&line[j]);
	if (j < 0)
		return (return_error("wrong path"));
	j += set_version(&line[j]);
	if (j < 0)
		return (return_error("wrong version"));
	if (line[j] != '\r')
	{
		response_code = BAD_REQUEST;
		return (return_error("")); //ERROR
	}
	return (OK);
}

int		Request::parse_headers(string line)
{
	(void)line;
	return (OK);
}

int		Request::parsing()
{
	string						line;
	int							i;

	i = 0;
	while(getline(cin, line))
	{
		if (i == 0 && first_line(line) != OK)
			return(response_code);
		else if (parse_headers(line) != OK)
				return(response_code);
		i++;
	}
	return(response_code);
}

int		main()
{
	Request	request;
	int				code;

	code = request.parsing();
	if (code != OK)
		return(code);
	request.print_debug();
}
