/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestCGI.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:58:35 by cdai              #+#    #+#             */
/*   Updated: 2021/11/14 21:31:31 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_CGI_HPP
# define REQUEST_CGI_HPP

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
};

#endif
