/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuilderCore.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:04:45 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/09 13:54:05 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BuilderCore.hpp"

BuilderCore::BuilderCore(std::istream &fd, Core *core) :
_idx(0),
_core(core)
{
	std::string	directive;
	std::getline(fd, _line, char(EOF));
	while (_line[_idx])
	{
		directive = next_word_skip();
		// std::cerr << "DIRECTIVE :\"" << directive << "\"" << std::endl;
		if (!directive.compare("worker"))
			parse_worker();
		else if (!directive.compare("server"))
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
		else if (directive != "")
		{
			std::cerr << "Parsing Error : unknown directive \"" << directive << "\" on line " << line_count() << std::endl;
			throw (ParsingError());
		}
	}
}

BuilderCore::~BuilderCore() {}

Core *
BuilderCore::get_builded_core() const
{
	return (_core);
}

std::string
BuilderCore::next_word_skip()
{
	skip_whitespaces();

	size_t			len = _line.find_first_of(";{}# \n\r\t\v\f", _idx) - _idx;

	if (len == std::string::npos)
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	std::string		ret = _line.substr(_idx, len);
	_idx += len;
	return(ret);
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
	// std::cerr << &_line[_idx] << std::endl;
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
	if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] == ';')
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
BuilderCore::parse_server_index(Server *server)
{
	std::string	index;

	skip_whitespaces();
	if (_line[_idx] == ';')
	{
		std::cerr << "Parsing Error : invalid number of arguments in \"index\" directive" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] == '}')
	{
		std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	while (_line[_idx] && _line[_idx] != ';' && _line[_idx] != '}')
	{
		index = next_word_skip();
		// std::cerr << "Index : " << index << std::endl; 
		server->add_index(index);
	}
	if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] == ';')
		_idx++;
	else if (_line[_idx] == '}')
	{
		std::cerr << "Parsing Error : unexpected \"}\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else
	{
		std::cerr << "Parsing Error : directive \"index\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
}

void
BuilderCore::parse_server_name(Server *server)
{
	std::string arg = next_word_skip();
	if (!arg.length())
	{
		if (_line[_idx] == ';')
			std::cerr << "Parsing Error : invalid number of arguments in \"server_name\" directive" << " on line " << line_count() << std::endl;
		else
			std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	server->set_name(arg);
	skip_whitespaces();
	if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] != ';')
	{
		std::cerr << "Parsing Error : directive \"server_name\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	_idx++;
}

void
BuilderCore::parse_server_root(Server *server)
{
	std::string arg = next_word_skip();
	if (!arg.length())
	{
		if (_line[_idx] == ';')
			std::cerr << "Parsing Error : invalid number of arguments in \"root\" directive" << " on line " << line_count() << std::endl;
		else
			std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	server->set_root(arg);
	skip_whitespaces();
	if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] != ';')
	{
		std::cerr << "Parsing Error : directive \"root\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
		_idx++;
}

void
BuilderCore::parse_server_path_error_page(Server *server)
{
	std::string arg = next_word_skip();
	if (!arg.length())
	{
		if (_line[_idx] == ';')
			std::cerr << "Parsing Error : invalid number of arguments in \"path_error_page\" directive" << " on line " << line_count() << std::endl;
		else
			std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	server->set_path_error_page(arg);
	skip_whitespaces();
	if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] != ';')
	{
		std::cerr << "Parsing Error : directive \"path_error_page\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	_idx++;
}

void
BuilderCore::parse_server_auto_index(Server *server)
{
	std::string arg = next_word_skip();
	if (!arg.compare("on"))
		server->set_auto_index(true);
	else if (!arg.compare("off"))
		server->set_auto_index(false);
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
	else if (arg != "")
	{
		std::cerr << "Parsing Error : invalid value \"" << arg << "\" in \"autoindex\" directive, it must be \"on\" or \"off\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	skip_whitespaces();
	if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] != ';')
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
BuilderCore::parse_server_CGI_param(CGI *cgi)
{
	skip_whitespaces();
	std::string key = next_word_skip();
	std::string value = next_word_skip();
	if (!key.length() || !value.length())
	{
		if (_line[_idx] == ';')
			std::cerr << "Parsing Error : invalid number of arguments in \"cgi_param\" directive" << " on line " << line_count() << std::endl;
		else
			std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	cgi->add_CGI_param(key, value);
	skip_whitespaces();
	if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] != ';')
	{
		std::cerr << "Parsing Error : directive \"path_error_page\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	_idx++;
}

void
BuilderCore::parse_server_CGI_exec_name(CGI *cgi)
{
	std::string arg = next_word_skip();
	if (!arg.length())
	{
		if (_line[_idx] == ';')
			std::cerr << "Parsing Error : invalid number of arguments in \"exec_name\" directive" << " on line " << line_count() << std::endl;
		else
			std::cerr << "Parsing Error : unexpected \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	cgi->set_exec_name(arg);
	skip_whitespaces();
	if (!_line[_idx])
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \";\" or \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	else if (_line[_idx] != ';')
	{
		std::cerr << "Parsing Error : directive \"path_error_page\" is not terminated by \";\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	_idx++;
}

void
BuilderCore::parse_server_extension(Server *server)
{
	std::string	directive;
	std::string extension_type = next_word_skip();
	skip_whitespaces();
	CGI cgi;
	if (_line [_idx++] != '{')
	{
		std::cerr << "Parsing Error : directive \"extension\" has no opening \"{\""  << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	skip_whitespaces();
	while (_line[_idx] && _line[_idx] != '}')
	{
		directive = next_word_skip();
		if (!directive.compare("cgi_param"))
			parse_server_CGI_param(&cgi);
		else if (!directive.compare("exec_name"))
			parse_server_CGI_exec_name(&cgi);
		else if (_line[_idx] ==  ';')
		{
			std::cerr << "Parsing Error : unexpected \";\"" << " on line " << line_count() << std::endl;
			throw (ParsingError());
		}
		else if (directive != "")
		{
			std::cerr << "Parsing Error : unknown directive \"" << directive << "\" on line " << line_count() << std::endl;
			throw (ParsingError());
		}
	}
	if (_line[_idx] != '}')
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	server->add_CGI(extension_type, cgi);
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
		directive = next_word_skip();
		// std::cerr << "directive : " << directive << " " << directive.length() << std::endl;
		// std::cerr << _idx - directive.length() << " " << directive.length() << std::endl;
		if (!directive.compare("listen"))
			parse_server_port(&server);
		else if (!directive.compare("server_name"))
			parse_server_name(&server);
		else if (!directive.compare("root"))
			parse_server_root(&server);
		else if (!directive.compare("autoindex"))
			parse_server_auto_index(&server);
		else if (!directive.compare("index"))
			parse_server_index(&server);
		else if (!directive.compare("client_max_body_size"))
			parse_server_client_max_body_size(&server);
		else if (!directive.compare("path_error_page"))
			parse_server_path_error_page(&server);
		else if (!directive.compare("extension"))
			parse_server_extension(&server);
		else if (_line[_idx] ==  ';')
		{
			std::cerr << "Parsing Error : unexpected \";\"" << " on line " << line_count() << std::endl;
			throw (ParsingError());
		}
		else if (directive != "")
		{
			std::cerr << "Parsing Error : unknown directive \"" << directive << "\" on line " << line_count() << std::endl;
			throw (ParsingError());
		}
	}
	if (_line[_idx] != '}')
	{
		std::cerr << "Parsing Error : unexpected end of file, expecting \"}\"" << " on line " << line_count() << std::endl;
		throw (ParsingError());
	}
	_core->add_server(server);
	server.print();
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

void
BuilderCore::parse_mime_type()
{
	Extension * extension = Extension::get_instance();
	_core->set_extension(extension);
}
