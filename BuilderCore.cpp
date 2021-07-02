/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuilderCore.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:04:45 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/02 16:53:05 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BuilderCore.hpp"

BuilderCore::BuilderCore(std::istream &fd, Core *core) :
_idx(0),
_core(core)
{
	std::getline(fd, _line, char(EOF));
	skip_whitespaces();
	while (_line[_idx])
	{
		if (!_line.compare(_idx, 7, "worker "))
			parse_worker();
		else if (!_line.compare(_idx, 7, "server "))
			parse_server();
		else if (!_line.compare(_idx, 1, "#"))
			skip_comments();
		else
		{
			std::cerr << "Parsing Error : unknown directive \"" << _line.substr(_idx, _line.find_first_of(";} \n\r\t\v\f", _idx) - _idx) << "\" on line " << line_count() << std::endl;
			throw (ParsingError());
		}
		skip_whitespaces();
	}
}

BuilderCore::~BuilderCore() {}

Core *
BuilderCore::get_builded_core() const
{
	return (_core);
}

int
BuilderCore::line_count()
{
	return (std::count(_line.begin(), _line.begin() + _idx, '\n'));
}

void
BuilderCore::skip_whitespaces()
{
	std::locale	loc;
	
	while (_line[_idx])
	{
		if (!std::isspace(_line[_idx], loc))
			return ;
		_idx++;
	}
}

void
BuilderCore::skip_comments()
{
	while (_line[_idx] == '#')
	{
		_idx += _line.find('\n') + 1;
		skip_whitespaces();
	}
}

void
BuilderCore::parse_server_port(Server *server)
{
	int	port;
	_idx += 7;
	skip_whitespaces();
	while (_line[_idx] && _line[_idx] != ';')
	{
		port = stoi_skip_number();
		server->add_port(port);
		skip_whitespaces();
	}
	if (_line[_idx] == ';')
		_idx++;
	else
	{
		std::cerr << "directive \"listen\" is not terminated by \";\"" << std::endl;
		throw (ParsingError());
	}
}

void
BuilderCore::parse_server_name(Server *server)
{
	_idx += 12;
	skip_whitespaces();
	size_t	len = _line.find_first_of(";} \n\r\t\v\f", _idx) - _idx;
	if (!len)
	{
		std::cerr << "Parsing Error : invalid number of arguments in \"server_name\" directive" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	server->set_name(_line.substr(_idx, len));
	_idx += len;
	skip_whitespaces();
	if (_line[_idx] != ';')
	{
		std::cerr << "directive \"server_name\" is not terminated by \";\"" << std::endl;
		throw (ParsingError());
	}
	_idx++;
}
void
BuilderCore::parse_server_root(Server *server)
{
	_idx += 5;
	skip_whitespaces();
	size_t	len = _line.find_first_of(";} \n\r\t\v\f", _idx) - _idx;
	if (!len)
	{
		std::cerr << "Parsing Error : invalid number of arguments in \"root\" directive" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	server->set_root(_line.substr(_idx, len));
	_idx += len;
	skip_whitespaces();
	if (_line[_idx] != ';')
	{
		std::cerr << "directive \"root\" is not terminated by \";\"" << std::endl;
		throw (ParsingError());
	}
		_idx++;
}

void
BuilderCore::parse_server_path_error_page(Server *server)
{
	_idx += 16;
	skip_whitespaces();
	size_t	len = _line.find_first_of(";} \n\r\t\v\f", _idx) - _idx;
	if (!len)
	{
		std::cerr << "Parsing Error : invalid number of arguments in \"path_error_page\" directive" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	server->set_path_error_page(_line.substr(_idx, len));
	_idx += len;
	skip_whitespaces();
	if (_line[_idx] != ';')
	{
		std::cerr << "directive \"path_error_page\" is not terminated by \";\"" << std::endl;
		throw (ParsingError());
	}
	_idx++;
}

void
BuilderCore::parse_server_auto_index(Server *server)
{
	_idx += 10;
	skip_whitespaces();
	if (!_line.compare(_idx, 2, "on"))
	{
		server->set_auto_index(true);
		_idx += 2;
	}
	else if (!_line.compare(_idx, 3, "off"))
	{
		server->set_auto_index(false);
		_idx += 3;
	}
	else
	{
		std::cerr << "invalid value \"" << _line.substr(_idx, _line.find_first_of(";} \n\r\t\v\f", _idx) - _idx) << "\" in \"autoindex\" directive, it must be \"on\" or \"off\"" << std::endl;
		throw (ParsingError());
	}
	skip_whitespaces();
	if (_line[_idx] != ';')
	{
		std::cerr << "directive \"autoindex\" is not terminated by \";\"" << std::endl;
		throw (ParsingError());
	}
	_idx++;
}

void
BuilderCore::parse_server_client_max_body_size(Server *server)
{
	_idx += 21;
	skip_whitespaces();
	size_t	client_max_body_size = stoi_skip_number();
	if (_line[_idx] == 'k' || _line[_idx] == 'K')
		client_max_body_size *= 1000;
	else if (_line[_idx] == 'm' || _line[_idx] == 'M')
		client_max_body_size *= 1000000;
	else if (_line[_idx] == 'g' || _line[_idx] == 'G')
		client_max_body_size *= 1000000000;
	else
		_idx--;
	_idx++;
	server->set_client_max_body_size(client_max_body_size);
	skip_whitespaces();
	if (_line[_idx] != ';')
	{
		std::cerr << "directive \"client_max_body_size\" is not terminated by \";\"" << std::endl;
		throw (ParsingError());
	}
	_idx++;
}

void
BuilderCore::parse_server()
{
	_idx += 7;
	skip_whitespaces();
	Server server;
	if (_line [_idx++] != '{')
	{
		std::cerr << "directive \"server\" has no opening \"{\"" << std::endl;
		throw (ParsingError());
	}
	skip_whitespaces();
	while (_line[_idx] && _line[_idx] != '}')
	{
		if (!_line.compare(_idx, 7, "listen "))
			parse_server_port(&server);
		else if (!_line.compare(_idx, 12, "server_name "))
			parse_server_name(&server);
		else if (!_line.compare(_idx, 5, "root "))
			parse_server_root(&server);
		else if (!_line.compare(_idx, 10, "autoindex "))
			parse_server_auto_index(&server);
		else if (!_line.compare(_idx, 21, "client_max_body_size "))
			parse_server_client_max_body_size(&server);
		else if (!_line.compare(_idx, 16, "path_error_page "))
			parse_server_path_error_page(&server);
		else
		{
			std::cerr << "Wrong directive in server" << std::endl;
			throw (ParsingError());
		}
		skip_whitespaces();
	}
	if (_line[_idx] != '}')
	{
		std::cerr << "unexpected end of file, expecting \"}\"" << std::endl;
		throw (ParsingError());
	}
	_core->add_server(server);
	_idx ++;
}

void
BuilderCore::parse_worker()
{
	_idx += 7;
	skip_whitespaces();
	int	worker = stoi_skip_number();
	skip_whitespaces();
	if (_line[_idx] == ';')
	{
		_core->set_worker(worker);
		_idx++;
		return ;
	}
	else
	{
		std::cerr << "directive \"worker\" is not terminated by \";\"" << std::endl;
		throw (ParsingError());
	}
}

int
BuilderCore::stoi_skip_number()
{
	int			ret;
	int			i = 0;
	std::locale loc;

	while(_line[i + _idx])
	{
		if (!isdigit(_line[i + _idx], loc))
			break ;
		i++;
	}
	if (!i)
	{
		std::cerr << "Missing number" << std::endl;
		throw (ParsingError());
	}
	std::stringstream ss(_line.substr(_idx, i));
	ss >> ret;
	_idx += i;
	return (ret);
}

void
BuilderCore::print_debug() const
{
	// std::cerr << &_line[_idx] << std::endl;
	// std::cerr << _idx << std::endl;
	std::cerr << "Worker : " << _core->get_worker() << std::endl;
	_core->print();
}
