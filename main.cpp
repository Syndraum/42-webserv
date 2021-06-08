/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:58:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/08 18:15:36 by mchardin         ###   ########.fr       */
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

class request_info
{
private:
	int		method;
	string	path;
	string version;
	int		response_code;

	string	error_msg(int code);
	int		return_error(string msg);
	int		which_method(string line);
	int		which_path(string line);
	int		which_version(string line);
	int		first_line(string line);
	int		parse_headers(string line);
	/* data */
public:
	request_info(/* args */);
	~request_info();

	int		parsing();
	void	print_debug();
};

request_info::request_info() : response_code(200)
{}

request_info::~request_info()
{}

void	request_info::print_debug()
{
	cerr << "METHOD CODE : " << method << " PATH : \"" << path << "\"";
}

string	request_info::error_msg(int code)
{
	if (code == BAD_REQUEST)
		return ("Bad Request");
	else if(code == BAD_VERSION)
		return ("HTTP Version Not Supported");
	else if(code == NOT_IMPLEMENTED)
		return("Not Implemented");
	return (0);
}

int		request_info::return_error(string msg)
{
	cout << response_code << " " << error_msg(response_code) << " : " << msg << endl;
	return(response_code);
}

int		request_info::which_method(string line)
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

int		request_info::which_path(string line)
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

int		request_info::which_version(string line)
{
	if (line.compare(0, 8, VERSION))
	{
		response_code = BAD_VERSION;
		return (-1);
	}
	version = VERSION;
	return (8);
}

int		request_info::first_line(string line)
{
	int	j = which_method(line);
	if (j < 0)
		return (return_error("wrong method"));
	j += which_path(&line[j]);
	if (j < 0)
		return (return_error("wrong path"));
	j += which_version(&line[j]);
	if (j < 0)
		return (return_error("wrong version"));
	if (line[j] != '\r')
	{
		response_code = BAD_REQUEST;
		return (return_error("wrong line end")); //ERROR
	}
	return (OK);
}

int		request_info::parse_headers(string line)
{
	(void)line;
	return (OK);
}

int		request_info::parsing()
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
	request_info	request;
	int				code;

	code = request.parsing();
	if (code != OK)
		return(code);
	request.print_debug();
}
