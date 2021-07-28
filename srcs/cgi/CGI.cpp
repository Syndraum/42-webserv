/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:35:26 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/25 15:14:05 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

CGI::CGI() :
_exec_name(),
_cgi_env(),
_handler(1)
{}

CGI::CGI(CGI const & src) : _handler(src._handler)
{
	*this = src;
}

CGI::~CGI(void)
{}

CGI &
CGI::operator=(CGI const &rhs)
{
	if (this != &rhs)
	{
		_exec_name = rhs._exec_name;
		_cgi_env = rhs._cgi_env;
		_handler = rhs._handler;
	}
	return (*this);
}

std::string &
CGI::get_exec_name(void)
{
	return (_exec_name);
}

void
CGI::set_exec_name(std::string const & name)
{
	_exec_name = name;
}

void
CGI::add_CGI_param(std::string key, std::string value)
{
	_cgi_env.insert(std::pair<std::string, std::string>(key, value));
}

size_t
CGI::str_table_len(char ** table) const
{
	size_t i = 0;
	
	while(table[i])
		i++;
	return (i);
}

void
CGI::str_table_delete(char ** table) const
{
	size_t i = 0;

	while(table[i])
	{
		delete table[i];
		i++;
	}
	delete table;
}

char *
CGI::string_copy(std::string str) const
{
	size_t i = -1;

	char * ret = new char[str.length() + 1];

	while(++i < str.length())
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

char **
CGI::create_env(const env_map & map)
{
	char **		cursor	= Info::env;
	char **		env;
	StringPP	line;
	int			i = 0;

	env = new char *[map.size() + str_table_len(Info::env) + 1];
	while (*cursor != 0)
	{
		env[i] = strdup(*cursor);
		i++;
		cursor++;
	}
	env_map::const_iterator ite = map.end();
	for (env_map::const_iterator it = map.begin(); it != ite; it++)
	{
		line = it->first + "=" + it->second;
		env[i] = line.string_copy();
		i++;
	}
	env[i] = 0;
	return (env);
}

void
CGI::join_env(env_map & my_env)
{
	env_map::iterator ite = _cgi_env.end();

	for (env_map::iterator it = _cgi_env.begin(); it != ite; it++)
		my_env[it->first] = it->second;
}

Message *
CGI::start(Message & request, const std::string & script_path)
{
	pid_t		pid;
	int			pipe_out[2];
	int			pipe_err[2];
	int			pipe_in[2];
	char **		env;

	env = create_env(request.get_headers());
	if (pipe(pipe_out) == -1 || pipe(pipe_err) == -1 || pipe(pipe_in) == -1)
		throw (std::exception()); // specify
	pid = fork();
	if (pid < 0)
		throw (std::exception()); // specify
	else if (!pid)
	{
		if (dup2(pipe_out[1], 1) == -1 || dup2(pipe_err[1], 2) == -1 || dup2(pipe_in[0], 0) == -1)
			throw (std::exception()); // specify
		close(pipe_out[0]);
		close(pipe_err[0]);
		close(pipe_in[1]);
		if (execle(_exec_name.c_str(), _exec_name.c_str(), script_path.c_str() ,NULL, env) < 0)
			throw (std::exception()); // specify
		_exit(0);
	}
	else
	{
		close(pipe_out[1]);
		close(pipe_err[1]);
		close(pipe_in[0]);
		write(pipe_in[1], request.get_body().c_str(), request.get_body().length());
		_handler.set_fd(pipe_out[0]);
		_handler.init();
		_handler.parse();
		close(pipe_out[0]);
		close(pipe_err[0]);
		close(pipe_in[1]);
	}
	str_table_delete(env);
	return (_handler.get_response());
}

void
CGI::print() const
{
	std::cout << "exec name : " << _exec_name << std::endl;
//	std::cout << "_arg : " << _arg << std::endl;

//	int i = -1;
//	while (_env[++i])
//		std::cerr << "_envi[i]: " << _env[i] << std::endl;
	std::cout << "CGI params : " << std::endl;
	for (env_map::const_iterator it = _cgi_env.begin(); it != _cgi_env.end(); it++)
	{
		std::cout << it->first << " = " << it->second << std::endl;
	}
}

void
CGI::print_env(char ** env) const
{
	char ** cursor = env;

	std::cout << "len: " << str_table_len(env) << std::endl;
	while (*cursor != 0)
	{
		std::cout << *cursor << std::endl;
		cursor++;
	}
}

void
CGI::_parse(int fd, Message & response)
{
	ReaderFileDescriptor	reader(fd);
	BuilderMessage			builder;
	std::string		line;
	int				gnl_ret = 1;
	
	builder.set_message(&response);
//	_builder.set_request(&get_request());
	while (gnl_ret && (gnl_ret = reader.get_next_line(line)))
	{
		if (gnl_ret == -1)
			return ;
		std::cout << "line: " << line << std::endl;
		line += "\r";
		builder._parse_headers(line);
		if (response.get_header_lock())
		{
			if (!response.has_header("Content-Length"))
			{
				std::cout << "No Content-Length" << std::endl;
				reader.read_until_end(line);
				//std::cout << "_buffer: " << _buffer << std::endl;
				response.set_body(line);
				// _response->add_header("Content-Length", line.size());
			}
			else
			{
				std::cout << "Content-Length : " << response.get_header("Content-Length") << std::endl;

				reader.read_body(line, std::atoi(response.get_header("Content-Length").c_str()));
				response.set_body(line);
				// _response->add_header("Content-Length", line.size());
			}
			response.set_body_lock(true);
//			get_client_socket().get_reader()._reset_buffer();
			gnl_ret = 0;
		}
	}
}
