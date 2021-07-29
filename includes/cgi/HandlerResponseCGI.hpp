/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerResponseCGI.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 16:19:18 by cdai              #+#    #+#             */
/*   Updated: 2021/07/28 18:20:43 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_RESPONSE_CGI_HPP
# define HANDLER_RESPONSE_CGI_HPP

# include <iostream>
# include "ReaderFileDescriptor.hpp"
# include "Response.hpp"
# include <cstdlib>

class HandlerResponseCGI
{
	private:
		ReaderFileDescriptor _reader;
		Response *			 _response;
		
		HandlerResponseCGI(void);

		void				_parse_headers(std::string line);
	public:
		HandlerResponseCGI(int);
		HandlerResponseCGI(HandlerResponseCGI const &);
		~HandlerResponseCGI(void);
		HandlerResponseCGI & operator=(HandlerResponseCGI const &);

		void	set_fd(int);
		void	set_response(Response *);
		void				parse(void);

};

#endif
