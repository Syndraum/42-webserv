/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:13:49 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 20:51:49 by mchardin         ###   ########.fr       */
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
# include "Array.hpp"
# include "Pipe.hpp"

class CGI
{
	public:

		typedef Message::map	env_map;

	private:
	
		std::string									_exec_name;
		env_map										_cgi_env;

		void										create_env(const env_map &, Array & array);
		void										join_env(env_map &);
		char**										create_env(void);

	public:

		CGI(void);
		CGI(CGI const & src);
		CGI &										operator=(CGI const &rhs);
		virtual ~CGI(void);
		
		std::string &								get_exec_name(void);
		void										set_exec_name(std::string const & name);
		void										add_CGI_param(std::string key, std::string value);

		pid_t										start(Message & request, const std::string & path, Pipe & pipes);
		class MyError: public std::exception
		{
			virtual const char*	what() const throw(){
				return "My error";
			}
		};
};

#endif
