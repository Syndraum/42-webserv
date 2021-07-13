/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestCGI.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:58:35 by cdai              #+#    #+#             */
/*   Updated: 2021/07/13 16:45:16 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTCGI_HPP
# define REQUESTCGI_HPP

# include <string>
# include <map>
# include "Response.hpp"
# include "CGI.hpp"

class RequestCGI
{
	private:
		std::map<std::string, std::string>	_env_cgi;
		CGI &								_cgi;
		Response							_response;
		RequestCGI(void);

	public:
		RequestCGI(CGI & cgi, std::map<std::string, std::string> & glob_env);
		~RequestCGI(void);
		RequestCGI const &					operator=(RequestCGI const &rhs);


		void								send(void);
		RequestCGI &						add_env(std::string key, std::string value);

		std::map<std::string, std::string>	get_env_cgi(void) const;
		CGI &								get_CGI(void) const;
		Response							get_response(void) const;
};

#endif
