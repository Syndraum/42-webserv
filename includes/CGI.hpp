/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:13:49 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/09 14:58:34 by mchardin         ###   ########.fr       */
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

class CGI
{
	public:

		typedef Message::map	env_map;

	private:
	
		std::string									_exec_name;
		env_map										_cgi_env;

		char **										create_env(const env_map &);
		void										join_env(env_map &);
		size_t										str_table_len(const char ** table) const;
		void										str_table_delete(char ** table) const;

	public:

		CGI(void);
		CGI(CGI const & src);
		CGI &										operator=(CGI const &rhs);
		virtual ~CGI(void);
		
		void										set_exec_name(std::string const & name);
		void										add_CGI_param(std::string key, std::string value);

		int											start(Message & request, const std::string & path);
		void										print() const;
		class MyError: public std::exception
		{
			virtual const char*	what() const throw(){
				return "My error";
			}
		};
};

#endif
