/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:35:26 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/09 14:59:23 by mchardin         ###   ########.fr       */
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
CGI::str_table_len(const char ** table) const
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

char **
CGI::create_env(const env_map & map)
{
	int				j = 0;
	StringPP		line;
	char **			env;

	env = new char *[map.size() + 1];
	env_map::const_iterator ite = map.end();
	for (env_map::const_iterator it = map.begin(); it != ite; it++)
	{
		line = it->first + "=" + it->second;
		env[j] = line.string_copy();
		j++;
	}
	env[j] = 0;
	return (env);
}

void
CGI::join_env(env_map & my_env)
{
	env_map::iterator ite = _cgi_env.end();

	for (env_map::iterator it = _cgi_env.begin(); it != ite; it++)
		my_env[it->first] = it->second;
}

int
CGI::start(Message & request)
{
	int			ret;
	pid_t		pid;
	// int			pipe_out[2];
	// int			pipe_err[2];
	char **		env;

	env = create_env(request.get_headers());
	// if (pipe(pipe_out) < 0 || pipe(pipe_err) < 0
	// || dup2(pipe_out[1], 1) < 0 || dup2(pipe_err[1], 2) < 0)
		// throw (std::exception()); // specify
	pid = fork();
	if (pid < 0)
		throw (std::exception()); // specify
	else if (!pid)
	{
		if (execle(_exec_name.c_str(), _exec_name.c_str(), NULL, env) < 0)
			throw (std::exception()); // specify
		_exit(0);
	}
	else
	{
		waitpid(pid, &ret, 0);
		// if (ret)
		// 	throw (std::exception()); // specify
		// close(pipe_out[1]);
		// close(pipe_err[1]);
		// close(pipe_err[0]);
	}
	str_table_delete(env);
	// return (pipe_out[0]);
	return (1);
}

void
CGI::print() const
{
	std::cerr << "exec name : " << _exec_name << std::endl;
	std::cerr << "CGI params : " << std::endl;
	for (env_map::const_iterator it = _cgi_env.begin(); it != _cgi_env.end(); it++)
	{
		std::cerr << it->first << " = " << it->second << std::endl;
	}
}
