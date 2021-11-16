/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuilderRequest.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:49:20 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/16 13:16:55 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_REQUEST_HPP
# define BUILDER_REQUEST_HPP

# include "Request.hpp"
# include "MethodLibrary.hpp"
# include <exception>
# include "Info.hpp"
# include "BuilderMessage.hpp"

class BuilderRequest : public BuilderMessage
{
	private:
	
		Request	*			_request;
		MethodLibrary *		_methods;

		BuilderRequest(BuilderRequest const & src);
		BuilderRequest &		operator=(BuilderRequest const &rhs);

		void					_first_line(std::string line);
		int						_add_method(std::string line);
		int						_add_path(std::string line);
		int						_add_version(std::string line);
	public:

		BuilderRequest(void);
		BuilderRequest(MethodLibrary *);
		virtual ~BuilderRequest(void);

		void					parse_request(std::string &);
		virtual void			set_message(Message *);
		void					set_library(MethodLibrary *);

		bool					is_first_line() const;

		class BadRequest : public std::exception
		{
			virtual const char*	what() const throw(){
				return "Bad Request";
			}
		};
		class BadHttpVersion : public std::exception
		{
			virtual const char* what() const throw(){
				return "HTTP Version Not Supported";
			}
		};
		class MethodNotImplemented : public std::exception
		{
			virtual const char* what() const throw(){
				return "Not Implemented";
			}
		};
};

#endif
