/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_request.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:19 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/24 21:35:58 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.hpp"

int		add_method(std::string line, Request *request)
{
	if (!line.compare(0, 4, "GET "))
	{
		request->set_method(GET);
		return (4);
	}
	else if (!line.compare(0, 5, "POST "))
	{
		request->set_method(POST);
		return (5);
	}
	else if (!line.compare(0, 7, "DELETE "))
	{
		request->set_method(DELETE);
		return (7);
	}
	else
		return (-1);
}

int		add_path(std::string line, Request *request)
{
	size_t		len = line.find(' ');
	if (len == std::string::npos)
		return(-1);
	request->set_path(line.substr(0, len));
	// check characters
	return(len + 1);
}

int		add_version(std::string line, Request *request)
{
	if (line.compare(0, 8, VERSION))
		return (-1);
	request->set_version(VERSION);
	return (8);
}

int		first_line(std::string line, Request *request)
{
	int	j = add_method(line, request);
	if (j < 0)
		return (NOT_IMPLEMENTED);
	j += add_path(&line[j], request);
	if (j < 0)
		return (BAD_REQUEST);
	j += add_version(&line[j], request);
	if (j < 0)
		return (BAD_VERSION);
	if (line[j] != '\r')
		return (BAD_REQUEST);
	return (OK);
}

int		parse_headers(std::string line, Request *request)
{
    size_t		len = line.find(": ");

	if (line[line.length() - 1] != '\r' || len == std::string::npos || line[len - 1] == ' ')
		return (BAD_REQUEST);
    request->add_header(std::pair<std::string, std::string>(line.substr(0, len), line.substr(len + 2, line.length() - len - 3)));
	return (OK);
}

int		parse_request(std::istream &fd, Request *request)
{
	std::string						line;
	int							i;
    int                         ret;

	i = 0;
	while(getline(fd, line))
	{
		//check printable characters
		if (i == 0)
        {
            if ((ret = first_line(line, request)) != OK)
                return(ret);
        }
		else if ((ret = parse_headers(line, request)) != OK)
				return(ret);
		i++;
	}
	return(ret);
}
