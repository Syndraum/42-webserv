/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:13:49 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/25 14:26:53 by cdai             ###   ########.fr       */
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
# include "Message.hpp"
# include "StringPP.hpp"
# include <cstring>
# include "Info.hpp"

class CGI
{
	public:

		typedef Message::map	env_map;

	private:
	
		std::string									_exec_name;
		env_map										_cgi_env;

		char **										create_env(const env_map &);
		void										join_env(env_map &);
		size_t										str_table_len(char ** table) const;
		void										str_table_delete(char ** table) const;
		char *										string_copy(std::string str) const;
		char**										create_env(void);

	public:

		CGI(void);
		CGI(CGI const & src);
		CGI &										operator=(CGI const &rhs);
		virtual ~CGI(void);
		
		std::string &								get_exec_name(void);
		void										set_exec_name(std::string const & name);
		void										add_CGI_param(std::string key, std::string value);

		int											start(Message & request, const std::string & path);
		void										print() const;
		void										print_env(char **) const;
		class MyError: public std::exception
		{
			virtual const char*	what() const throw(){
				return "My error";
			}
		};
};

#endif
