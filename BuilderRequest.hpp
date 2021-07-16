/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuilderRequest.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:49:20 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/02 16:00:18 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDERREQUEST
# define BUILDERREQUEST

# include "Request.hpp"
# include "ASocket.hpp"
# include <exception>
# include "MethodLibrary.hpp"
# include "Info.hpp"

class BuilderRequest
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
		bool					_parse_headers(std::string line);
	public:

		BuilderRequest(void);
		BuilderRequest(MethodLibrary *);
		virtual ~BuilderRequest(void);

		void					parse_request(ASocket &);
		Request *				get_request() const;
		void					set_request(Request *);
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
		class NoRequest : public std::exception
		{
			virtual const char* what() const throw(){
				return "NoRequest";
			}
		};
};

#endif
