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

char**
CGI::create_env(void)
{
	char** result;
	int i = 0;


	result = new char*[_cgi_env.size() + 1];
	for (env_map::iterator it = _cgi_env.begin(); it != _cgi_env.end(); it++)
	{
		std::string temp = it->first + "=" + it->second;
		result[i] = strdup(temp.c_str());
		i++;
	}
	result[i] = NULL;
	return (result);
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
CGI::start(Message & request, const std::string & script_path)
{
	int			ret;
	pid_t		pid;
	int			pipe_out[2];
	// int			pipe_err[2];
	char **		env;

	std::cout << "s_P : " << script_path.c_str() << std::endl;
	env = create_env(request.get_headers());
	if (pipe(pipe_out))
		throw (std::exception()); // specify
	pid = fork();
	if (pid < 0)
		throw (std::exception()); // specify
	else if (!pid)
	{
		close(pipe_out[0]);
		dup2(pipe_out[1], 1);
		if (execle(_exec_name.c_str(), _exec_name.c_str(), script_path.c_str() ,NULL, env) < 0)
			throw (std::exception()); // specify
		close(pipe_out[0]);
		_exit(0);
	}
	else
	{
		close(pipe_out[1]);
		waitpid(pid, &ret, 0);
//		char buffer[32];
//		int read_ret = read(pipe_out[0], buffer, 31);
//		buffer[read_ret] = 0;
//		std::cout << "buffer : " << buffer << std::endl;
	}
	str_table_delete(env);
	return (pipe_out[0]);
	return (1);
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
