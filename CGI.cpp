/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:35:26 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/09 13:55:01 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

CGI::CGI() :
_env(0)
{}

CGI::CGI(std::string exec_name, char * arg, env_map glob_env, env_map my_env):
_exec_name(exec_name),
_arg(arg),
_env(join_env(glob_env, my_env))
{}

CGI::~CGI(void)
{
	if (_env)
		str_table_delete(_env);
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
CGI::join_env(env_map glob_env, env_map my_env)
{
	int				j = 0;
	std::string		tmp_str;
	char **			ret;

	env_map::iterator ite = glob_env.end();

	for (env_map::iterator it = glob_env.begin(); it != ite; it++)
		my_env[it->first] = it->second;
	ret = new char *[my_env.size() + 1];
	env_map::iterator ite2 = my_env.end();

	for (env_map::iterator it = my_env.begin(); it != ite2; it++)
	{
		tmp_str = it->first + "=" + it->second;
		ret[j] = string_copy(tmp_str);
		j++;
	}
	ret[j] = 0;
	return (ret);
}

int
CGI::start()
{
	int			ret;
	pid_t		pid = fork();
	int			pipe_out[2];
	int			pipe_err[2];

	if (pipe(pipe_out) < 0 || pipe(pipe_err) < 0
	|| dup2(pipe_out[1], 1) < 0 || dup2(pipe_err[1], 2) < 0)
		throw (std::exception()); // specify
	if (pid < 0)
		throw (std::exception()); // specify
	else if (!pid)
	{
		if (execle(_exec_name.c_str(), _arg, _env) < 0)
			throw (std::exception()); // specify
		_exit(0);
	}
	else
	{
		waitpid(pid, &ret, 0);
		if (ret)
			throw (std::exception()); // specify
		close(pipe_out[1]);
		close(pipe_err[1]);
		close(pipe_err[0]);
	}
	return (pipe_out[0]);
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