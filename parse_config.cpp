/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:04:45 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/24 10:38:57 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"
#include <cctype>

int		count_whitespace(std::string line)
{
	for (int i = 0; i < line.length(); i++)
		if (!isspace(line[i]))
			return (i);
	return (line.length());
}

int		skip_comment(std::string line)
{
	return(line.find('\n') + 1);
}

int		parse_server_port(std::string line, Server *server)
{
	int i = count_whitespace(line);
	int	port;

	while(line[i] != ';' && line[i] != '}')
	{
		try { port = std::stoi(&line[i], &i); }
		catch (std::exception &e) { return (-1); }
		server->add_port(port);
		i += count_whitespace(&line[i]);
	}
	return (i + (line[i] == ';'));
}

parse_server_name(std::string line, Server *server)
{
	int i = count_whitespace(line);
	size_t	len = line.find_first_of(";} \n\r\t\v\f");

	if (!len)
		return (-1);
	server->set_name(line.substr(i, len - 1));
	return (i + (line[i] == ';'));
}

parse_server(std::string line, Core *core)
{
	int i = count_whitespace(line);
	Server server;
	if (line [i++] != '{')
		return (-1);
	while (line[i] != '}')
	{
		i += count_whitespace(line);
		if (!line.compare(i, 7, "listen "))
		{
			if ((ret = parse_server_port(&line[i + 7], server)) < 0)
				return (ret);
		}
		else if (!line.compare(i, 12, "server_name "))
		{
			if ((ret = parse_server_name(&line[i + 12], server)) < 0)
				return (ret);
		}
		else if (!line.compare(i, 5, "root "))
		{
			if ((ret = parse_server_root(&line[i + 5], server)) < 0)
				return (ret);
		}
		else if (!line.compare(i, 6, "index "))
		{
			if ((ret = parse_server_index(&line[i + 6], server)) < 0)
				return (ret);
		}
		else if (!line.compare(i, 10, "autoindex "))
		{
			if ((ret = parse_server_autoindex(&line[i + 10], server)) < 0)
				return (ret);
		}
		else if (!line.compare(i, 21, "client_max_body_size "))
		{
			if ((ret = parse_server_body_size(&line[i + 21], server)) < 0)
				return (ret);
		}
		else if (!line.compare(i, 16, "path_error_page "))
		{
			if ((ret = parse_server_error_page(&line[i + 16], server)) < 0)
				return (ret);
		}
		i += ret;
	}
	core->add_server(server);
	return (i);
}

parse_worker(std::string line, Core *core)
{
	int i = count_whitespace(line);
	int	worker;
	try { worker = std::stoi(&line[i], &i); }
	catch (std::exception &e) { return (-1); }
	i += count_whitespace(&line[i]);
	if (line[i] == ';')
	{
		core->set_worker(worker);
		return (i + 1);
	}
	return (-1);
}

int		parse_config(std::istream fd, Core *core)
{
	string						line;
	size_t						i;
    int                         ret;

	i = 0;
	getline(fd, line, std::eof);
	while (line[i])
	{
		i += count_whitespace(line);
		if (!line.compare(i, 7, "worker ")
		{
			if ((ret = parse_worker(&line[i + 7], core)) < 0)
				return (ret);
		}
		else if (!line.compare(i, 7, "server ")
		{
			if (ret = parse_server(&line[i + 7], core)) < 0)
				return (ret);
		}
		else if (!line.compare(i, 1, "#")
			ret = skip_comment(&line[i + 1]);
		else
			return (-1); // determine specific errors
		i += ret;
	}
	return (ret);
}
