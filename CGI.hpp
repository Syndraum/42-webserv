/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:13:49 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/07 15:02:59 by mchardin         ###   ########.fr       */
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

		CGI(void);
		CGI(CGI const & src);
		CGI &										operator=(CGI const &rhs);
		char **										join_env(char ** envp, std::map<std::string, std::string> my_env);
		int											str_table_len(const char ** table) const;
		void										str_table_delete(const char ** table) const;
		char *										string_copy(std::string str) const;
	
	public:

		CGI(std::string exec_name, char * arg, char ** envp, env_map my_env);
		virtual ~CGI(void);
		int											start();
		class MyError: public std::exception
		{
			virtual const char*	what() const throw(){
				return "My error";
			}
		};
};

#endif
