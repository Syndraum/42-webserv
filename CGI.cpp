/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 18:35:26 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/07 12:19:44 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

int
CGI::str_table_len(const char ** table) const
{
	int i = 0;
	
	while(table[i])
		i++;
	return (i);
}

void
CGI::str_table_delete(const char ** table) const
{
	int i = 0;

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
	int i = -1;

	char * ret = new char[str.length() + 1];

	while(++i < str.length())
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

char **
CGI::join_env(char **envp, env_map my_env)
{
	int				len = str_table_len(envp);
	int				j = 0;
	std::string		tmp_str;
	char **			ret;

	ret = new char *[my_env.size() + len + 1];

	for (int i = 0; i < len; i++)
		ret[i] = envp[i];
	env_map::iterator ite = my_env.end();

	for (env_map::iterator it = my_env.begin(); it != ite; it++)
	{
		tmp_str = it->first + "=" + it->second;
		ret[len + j] = string_copy(tmp_str);
		j++;
	}
	ret[len + j] = 0;
	return (ret);
}

CGI::CGI(char **envp, env_map my_env, std::string exec_name):
_env(join_env(envp, my_env)),
_exec_name(exec_name)
{}

CGI::~CGI(void)
{
	str_table_delete(_env);
}

void
CGI::start()
{
	pid_t		pid;

	
}