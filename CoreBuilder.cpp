/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CoreBuilder.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:04:45 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/30 15:03:12 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CoreBuilder.hpp"
#include <cctype>

void	CoreBuilder::skip_whitespaces()
{
	while(_line[_idx])
	{
		if (!isspace(_line[_idx]))
			return ;
		_idx++;
	}
}

void	CoreBuilder::skip_comments()
{
	while(_line[_idx] == '#')
	{
		_idx += _line.find('\n') + 1;
		skip_whitespaces();
	}
}

void	CoreBuilder::parse_server_port(Server *server)
{
	int	port;
	_idx += 7;
	skip_whitespaces();
	while(_line[_idx] != ';' && _line[_idx] != '}')
	{
		try { port = std::stoi(&_line[_idx], &_idx); }
		catch (std::exception &e) { throw (std::exception()); }
		server->add_port(port);
		skip_whitespaces();
	}
	if(_line[_idx] == ';')
		_idx++;
}

void	CoreBuilder::parse_server_string(Server *server, int directive_len, void (*setter)(std::string))
{
	_idx += directive_len;
	skip_whitespaces();
	size_t	len = _line.find_first_of(";} \n\r\t\v\f");
	if (!len)
		throw (std::exception());
	setter(_line.substr(_idx, len - 1));
	_idx += len;
	skip_whitespaces();
	if (_line[_idx] != ';' && _line[_idx] != '}')
		throw (std::exception());
	if(_line[_idx] == ';')
		_idx++;
}

void	CoreBuilder::parse_server_auto_index(Server *server)
{
	_idx += 10;
	skip_whitespaces();
	if (_line.compare(_idx, 2, "on"))
		server->set_root(1);
	else if (_line.compare(_idx, 3, "off"))
		server->set_root(0);
	else
		throw (std::exception());
	skip_whitespaces();
	if (_line[_idx] != ';' && _line[_idx] != '}')
		throw (std::exception());
	if(_line[_idx] == ';')
		_idx++;
}

void	CoreBuilder::parse_server_client_max_body_size(Server *server)
{
	int	client_max_body_size;
	_idx += 21;
	skip_whitespaces();
	try { client_max_body_size = std::stoi(&_line[_idx], &_idx); }
	catch (std::exception &e) { throw (std::exception()); }
	server->set_client_max_body_size(client_max_body_size);
	skip_whitespaces();
	if (_line[_idx] != ';' && _line[_idx] != '}')
		throw (std::exception());
	if(_line[_idx] == ';')
		_idx++;
}

void	CoreBuilder::parse_server()
{
	_idx += 7;
	skip_whitespaces();
	Server *server;
	if (_line [_idx++] != '{')
		throw (std::exception());
	while (_line[_idx] != '}')
	{
		skip_whitespaces(_line);
		if (!_line.compare(_idx, 7, "listen "))
			parse_server_port(server);
		else if (!_line.compare(_idx, 12, "server_name "))
			parse_server_string(server, 12, server->set_name());
		else if (!_line.compare(_idx, 5, "root "))
			parse_server_string(server, , 5, server->set_root());
		// else if (!_line.compare(_idx, 6, "index "))
		// 	parse_server_string(server, 6, server->set_index());
		else if (!_line.compare(_idx, 10, "auto_index "))
			parse_server_auto_index(server);
		else if (!_line.compare(_idx, 21, "client_max_body_size "))
			parse_server_client_max_body_size(server);
		else if (!_line.compare(_idx, 16, "path_error_page "))
			parse_server_string(server, 16, server->set_error_page());
	}
	core->add_server(server);
}

void	CoreBuilder::parse_worker()
{
	_idx += 7;
	skip_whitespaces();
	int	worker;
	try { worker = std::stoi(&_line[_idx], &_idx); }
	catch (std::exception &e) { throw (std::exception()); }
	skip_whitespaces();
	if (_line[_idx] == ';')
	{
		core->set_worker(worker);
		return ;
	}
	throw (std::exception());
}

CoreBuilder::CoreBuilder(std::istream fd, Core *core) : _idx(0), _core(core)
{
	std::getline(fd, _line, char(EOF));
	while (_line[_idx])
	{
		skip_whitespaces();
		if (!_line.compare(_idx, 7, "worker "))
			parse_worker();
		else if (!_line.compare(_idx, 7, "server "))
			parse_server();
		else if (!_line.compare(_idx, 1, "#"))
			skip_comments();
		else
			throw (std::exception()); // determine specific errors
	}
}

CoreBuilder::~CoreBuilder()
{}

Core	*CoreBuilder::get_builded_core() const
{
	return (_core);
}
