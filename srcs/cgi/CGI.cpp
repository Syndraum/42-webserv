/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:35:26 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 20:24:41 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

CGI::CGI() :
_exec_name(),
_cgi_env()
{}

CGI::CGI(CGI const & src)
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

pid_t
CGI::start(Message & request, const std::string & script_path, Pipe & pipes)
{
	pid_t			pid;
	int *			pipe_out	= pipes.get_out();
	int	*			pipe_err	= pipes.get_err();
	int	*			pipe_in		= pipes.get_in();
	Array			a_env;

	create_env(request.get_headers(), a_env);
	if (pipe(pipe_out) == -1 || pipe(pipe_err) == -1 || pipe(pipe_in) == -1)
		throw (std::exception());
	pid = fork();
	if (pid < 0)
		throw (std::exception());
	else if (!pid)
	{
		if (dup2(pipe_out[1], 1) == -1 || dup2(pipe_err[1], 2) == -1 || dup2(pipe_in[0], 0) == -1)
			_exit(2);
		close(pipe_out[0]);
		close(pipe_err[0]);
		close(pipe_in[1]);
		if (execle(_exec_name.c_str(), _exec_name.c_str(), script_path.c_str() ,NULL, a_env.data()) == -1){
			_exit(1);
		}
		_exit(0);
	}
	else
	{
		close(pipe_out[1]);
		close(pipe_err[1]);
		close(pipe_in[0]);
	}
	return (pid);
}

void
CGI::print() const
{
	std::cout << "exec name : " << _exec_name << std::endl;
	std::cout << "CGI params : " << std::endl;
	for (env_map::const_iterator it = _cgi_env.begin(); it != _cgi_env.end(); it++)
	{
		std::cout << it->first << " = " << it->second << std::endl;
	}
}
