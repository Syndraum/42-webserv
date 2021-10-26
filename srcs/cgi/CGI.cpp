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

void
CGI::create_env(const env_map & map, Array & array)
{
	char **		cursor	= Info::env;
	StringPP	line;

	array.set_capacity(map.size() + Array::len(Info::env));
	while (*cursor != 0)
	{
		array.push_back(*cursor);
		cursor++;
	}
	env_map::const_iterator ite = map.end();
	for (env_map::const_iterator it = map.begin(); it != ite; it++)
	{
		line = StringPP::to_upper(it->first) + "=" + it->second;
		array.push_back(line.str().c_str());
	}
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
	pid_t			pid;
	int				pipe_out[2];
	int				pipe_err[2];
	int				pipe_in[2];
	Array		a_env;
	// char **		env;

	// env = create_env(request.get_headers());
	create_env(request.get_headers(), a_env);
	if (pipe(pipe_out) == -1 || pipe(pipe_err) == -1 || pipe(pipe_in) == -1)
		throw (std::exception()); // specify
	pid = fork();
	if (pid < 0)
		throw (std::exception()); // specify
	else if (!pid)
	{
		if (dup2(pipe_out[1], 1) == -1 || dup2(pipe_err[1], 2) == -1 || dup2(pipe_in[0], 0) == -1)
			_exit(2);
			// throw (std::exception()); // specify
		close(pipe_out[0]);
		close(pipe_err[0]);
		close(pipe_in[1]);
		if (execle(_exec_name.c_str(), _exec_name.c_str(), script_path.c_str() ,NULL, a_env.data()) == -1){
			_exit(1);
			// throw (std::exception()); // specify
		}
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
		_handler.parse(); // MAYBE WHILE
		close(pipe_out[0]);
		close(pipe_err[0]);
		close(pipe_in[1]);
	}
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
