/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerResponseCGI.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 16:19:18 by cdai              #+#    #+#             */
/*   Updated: 2021/07/25 18:06:27 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_RESPONSE_CGI
# define HANDLER_RESPONSE_CGI

# include <iostream>
# include "ReaderFileDescriptor.hpp"
# include "BuilderMessage.hpp"
# include "Message.hpp"
# include <cstdlib>

class HandlerResponseCGI
{
	private:
		ReaderFileDescriptor	_reader;
		BuilderMessage			_builder;
		Message *				_response;
		
		HandlerResponseCGI(void);

	public:
		HandlerResponseCGI(int);
		HandlerResponseCGI(HandlerResponseCGI const &);
		~HandlerResponseCGI(void);
		HandlerResponseCGI & operator=(HandlerResponseCGI const &);

		void		set_fd(int);
		Message *	get_response();
		void		init();
		void		clear();
		void		parse();

};

#endif
