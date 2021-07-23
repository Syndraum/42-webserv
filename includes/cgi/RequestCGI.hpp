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
# include "Message.hpp"
# include "CGI.hpp"

class RequestCGI : public Message
{
	private:
		CGI &								_cgi;
		RequestCGI(void);

	public:
		RequestCGI(CGI & cgi);
		~RequestCGI(void);
		RequestCGI const &					operator=(RequestCGI const &rhs);


		void								send(const std::string &);
};

#endif
