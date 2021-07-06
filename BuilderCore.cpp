/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuilderCore.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:04:45 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/05 20:52:51 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BuilderCore.hpp"

BuilderCore::BuilderCore(std::istream &fd, Core *core) :
_idx(0),
_core(core)
{
	std::string	directive;
	std::getline(fd, _line, char(EOF));
	skip_whitespaces();
	while (_line[_idx])
	{
		directive = _line.substr(_idx, _line.find_first_of(";{}# \n\r\t\v\f", _idx) - _idx);
		_idx += directive.length();
		if (!_line.compare(_idx - directive.length(), directive.length(), "worker"))
			parse_worker();
		else if (!_line.compare(_idx - directive.length(), directive.length(), "server"))
			parse_server();
		else if (_line[_idx] ==  ';')
		{
			std::cerr << "Parsing Error : unexpected \";\"" << " on line " << line_count() << std::endl;
			throw (ParsingError());
		}
		else if (_line[_idx] ==  '}')
		{
			std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
			throw (ParsingError());
		}
		else
		{
			std::cerr << "Parsing Error : unknown directive \"" << directive << "\" on line " << line_count() << std::endl;
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
	return (std::count(_line.begin(), _line.begin() + _idx, '\n') + 1);
}

void
BuilderCore::skip_whitespaces()
{
	std::locale	loc;
	
	while (_line[_idx])
	{
		if (_line[_idx] ==  '#')
			skip_comments();
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
		_idx = _line.find('\n', _idx) + 1;
		skip_whitespaces();
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
	if (!_line[i + _idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (!i)
		return (-1);
	std::stringstream ss(_line.substr(_idx, i));
	ss >> ret;
	_idx += i;
	return (ret);
}

void
BuilderCore::parse_server_port(Server *server)
{
	int	port;

	skip_whitespaces();
	if (_line[_idx] == ';')
	{
		std::cerr << "Parsing Error : invalid number of arguments in \"listen\" directive" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] == '}')
	{
		std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	while (_line[_idx] && _line[_idx] != ';' && _line[_idx] != '}')
	{
		port = stoi_skip_number();
		if (port < 0)
		{
			std::cerr << "Parsing Error : host not found in \"" << _line.substr(_idx, _line.find_first_of(";}# \n\r\t\v\f", _idx) - _idx) << "\" of the \"listen\" directive"  << " on line " << line_count() << std::endl;
			throw (ParsingError());
		}
		server->add_port(port);
		skip_whitespaces();
	}
	if (_line[_idx] == ';')
		_idx++;
	else if (_line[_idx] == '}')
	{
		std::cerr << "Parsing Error : unexpected \"}\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else
	{
		std::cerr << "Parsing Error : directive \"listen\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
}

void
BuilderCore::parse_server_name(Server *server)
{
	skip_whitespaces();
	size_t	len = _line.find_first_of(";}# \n\r\t\v\f", _idx) - _idx;
	if (!len)
	{
		if (_line[_idx] == ';')
			std::cerr << "Parsing Error : invalid number of arguments in \"server_name\" directive" << " on line " << line_count() << std::endl;
		else
			std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (len == std::string::npos)
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	server->set_name(_line.substr(_idx, len));
	_idx += len;
	skip_whitespaces();
	if (_line[_idx] != ';')
	{
		std::cerr << "Parsing Error : directive \"server_name\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	_idx++;
}
void
BuilderCore::parse_server_root(Server *server)
{
	skip_whitespaces();
	size_t	len = _line.find_first_of(";}# \n\r\t\v\f", _idx) - _idx;
	if (!len)
	{
		if (_line[_idx] == ';')
			std::cerr << "Parsing Error : invalid number of arguments in \"root\" directive" << " on line " << line_count() << std::endl;
		else
			std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (len == std::string::npos)
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	server->set_root(_line.substr(_idx, len));
	_idx += len;
	skip_whitespaces();
	if (_line[_idx] != ';')
	{
		std::cerr << "Parsing Error : directive \"root\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
		_idx++;
}

void
BuilderCore::parse_server_path_error_page(Server *server)
{
	skip_whitespaces();
	size_t	len = _line.find_first_of(";}# \n\r\t\v\f", _idx) - _idx;
	if (!len)
	{
		if (_line[_idx] == ';')
			std::cerr << "Parsing Error : invalid number of arguments in \"path_error_page\" directive" << " on line " << line_count() << std::endl;
		else
			std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (len == std::string::npos)
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	server->set_path_error_page(_line.substr(_idx, len));
	_idx += len;
	skip_whitespaces();
	if (_line[_idx] != ';')
	{
		std::cerr << "Parsing Error : directive \"path_error_page\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	_idx++;
}

void
BuilderCore::parse_server_auto_index(Server *server)
{
	skip_whitespaces();
	if (!_line.compare(_idx, 2, "on") && _line.find_first_of(";}# \n\r\t\v\f", _idx + 2) == _idx + 2)
	{
		server->set_auto_index(true);
		_idx += 2;
	}
	else if (!_line.compare(_idx, 3, "off") && _line.find_first_of(";}# \n\r\t\v\f", _idx + 3) == _idx + 3)
	{
		server->set_auto_index(false);
		_idx += 3;
	}
	else if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] == ';')
	{
		std::cerr << "Parsing Error : invalid number of arguments in \"autoindex\" directive" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] == '}')
	{
		std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else
	{
		std::cerr << "Parsing Error : invalid value \"" << _line.substr(_idx, _line.find_first_of(";}# \n\r\t\v\f", _idx) - _idx) << "\" in \"autoindex\" directive, it must be \"on\" or \"off\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	skip_whitespaces();
	if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	if (_line[_idx] != ';')
	{
		std::cerr << "Parsing Error : directive \"autoindex\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	_idx++;
}

void
BuilderCore::parse_server_client_max_body_size(Server *server)
{
	std::locale		loc;
	int				ret;
	size_t			client_max_body_size;

	skip_whitespaces();
	if (_line[_idx] == ';')
	{
		std::cerr << "Parsing Error : invalid number of arguments in \"client_max_body_size\" directive" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] == '}')
	{
		std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	ret = stoi_skip_number();
	if (ret < 0)
	{
		std::cerr << "Parsing Error : \"client_max_body_size\" directive invalid value"  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	client_max_body_size = ret;
	if (_line[_idx] == 'k' || _line[_idx] == 'K')
		client_max_body_size *= 1000;
	else if (_line[_idx] == 'm' || _line[_idx] == 'M')
		client_max_body_size *= 1000000;
	else if (_line[_idx] == 'g' || _line[_idx] == 'G')
		client_max_body_size *= 1000000000;
	else if (_line.find_first_of(";}# \n\r\t\v\f", _idx) == _idx)
		_idx--;
	else if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else
	{
		std::cerr << "Parsing Error : \"client_max_body_size\" directive invalid value"  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	_idx++;
	server->set_client_max_body_size(client_max_body_size);
	skip_whitespaces();
	if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] != ';')
	{
		std::cerr << "Parsing Error : directive \"client_max_body_size\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	_idx++;
}

void
BuilderCore::parse_server()
{
	skip_whitespaces();
	std::string	directive;
	Server server;
	if (_line [_idx++] != '{')
	{
		std::cerr << "Parsing Error : directive \"server\" has no opening \"{\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	skip_whitespaces();
	while (_line[_idx] && _line[_idx] != '}')
	{
		directive = _line.substr(_idx, _line.find_first_of(";{}# \n\r\t\v\f", _idx) - _idx);
		// std::cerr << "directive : " << directive << " " << directive.length() << std::endl;
		_idx +=  directive.length();
		// std::cerr << _idx - directive.length() << " " << directive.length() << std::endl;
		if (!_line.compare(_idx - directive.length(), directive.length(), "listen"))
			parse_server_port(&server);
		else if (!_line.compare(_idx - directive.length(), directive.length(), "server_name"))
			parse_server_name(&server);
		else if (!_line.compare(_idx - directive.length(), directive.length(), "root"))
			parse_server_root(&server);
		else if (!_line.compare(_idx - directive.length(), directive.length(), "autoindex"))
			parse_server_auto_index(&server);
		else if (!_line.compare(_idx - directive.length(), directive.length(), "client_max_body_size"))
			parse_server_client_max_body_size(&server);
		else if (!_line.compare(_idx - directive.length(), directive.length(), "path_error_page"))
			parse_server_path_error_page(&server);
		else if (_line[_idx] ==  ';')
		{
			std::cerr << "Parsing Error : unexpected \";\"" << " on line " << line_count() << std::endl;
			throw (ParsingError());
		}
		else
		{
			std::cerr << "Parsing Error : Wrong directive in server" << " on line " << line_count() << std::endl;
			throw (ParsingError());
		}
		skip_whitespaces();
	}
	if (_line[_idx] != '}')
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	_core->add_server(server);
	_idx ++;
}

void
BuilderCore::parse_worker()
{
	skip_whitespaces();
	if (_line[_idx] == ';')
	{
		std::cerr << "Parsing Error : invalid number of arguments in \"worker\" directive" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] == '}')
	{
		std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	int	worker = stoi_skip_number();
	if (worker < 0)
	{
		std::cerr << "Parsing Error : invalid number \"" << _line.substr(_idx, _line.find_first_of(";}# \n\r\t\v\f", _idx) - _idx) << "\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	skip_whitespaces();
	if (_line[_idx] == ';')
	{
		_core->set_worker(worker);
		_idx++;
		return ;
	}
	else if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else
	{
		std::cerr << "Parsing Error : directive \"worker\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
}

void
BuilderCore::print_debug() const
{
	// std::cerr << &_line[_idx] << std::endl;
	// std::cerr << _idx << std::endl;
	std::cerr << "Worker : " << _core->get_worker() << std::endl;
	_core->print();
}
