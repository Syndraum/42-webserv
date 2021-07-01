/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuilderRequest.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:49:20 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:49:21 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDERREQUEST
# define BUILDERREQUEST

# include "Request.hpp"
# include "ASocket.hpp"
# include <exception>
# include "MethodLibrary.hpp"

class BuilderRequest
{
	private:
	
		Request	*				_request;
		MethodLibrary &			_methods;

		BuilderRequest(void);
		BuilderRequest(BuilderRequest const & src);
		BuilderRequest &		operator=(BuilderRequest const &rhs);

	public:

		BuilderRequest(MethodLibrary &);
		virtual ~BuilderRequest(void);

		int						add_method(std::string line);
		int						add_path(std::string line);
		int						add_version(std::string line);
		void					first_line(std::string line);
		bool					parse_headers(std::string line);
		void					parse_request(ASocket &);
		Request *				get_request() const;
		void					reset();

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
