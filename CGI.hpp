/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:13:49 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/09 13:49:25 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include <exception>
# include <map>
# include <iostream>
# include <string>
# include <sys/wait.h>
# include <unistd.h>

class CGI
{
	public:

		typedef std::map<std::string, std::string>	env_map;

	private:
	
		std::string									_exec_name;
		char *										_arg;
		char **										_env;
		env_map										_cgi_env;

		// CGI(CGI const & src);
		// CGI &										operator=(CGI const &rhs);
		char **										join_env(env_map glob_env, env_map my_env);
		size_t										str_table_len(const char ** table) const;
		void										str_table_delete(char ** table) const;
		char *										string_copy(std::string str) const;

	public:

		CGI(void);
		CGI(std::string exec_name, char * arg, env_map glob_env, env_map my_env);
		virtual ~CGI(void);
		
		void										set_exec_name(std::string const & name);
		void										add_CGI_param(std::string key, std::string value);

		int											start();
		void										print() const;
		class MyError: public std::exception
		{
			virtual const char*	what() const throw(){
				return "My error";
			}
		};
};

#endif
