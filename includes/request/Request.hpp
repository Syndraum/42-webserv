/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:27:00 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/22 12:40:05 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "Message.hpp"
# include "URI.hpp"

class AMethod;
class Response;

class Request : public Message
{
	private:

		AMethod	*									_method;
		URI											_uri;
		std::string									_version;

	public:
	
		class NoMethod : public std::exception
		{
			virtual const char* what() const throw(){
				return "NoMethod";
			}
		};
		Request();
		Request(Request const &rhs);
		~Request();
		Request const &								operator=(Request const &rhs);

		AMethod *									get_method() const;
		std::string const &							get_path() const;
		URI &										get_uri();
		const URI &									get_uri() const;
		std::string const &							get_version() const;

		void										set_method(AMethod * rhs);
		void										set_path(std::string const &rhs);
		void										set_uri(std::string const &rhs);
		void										set_version(std::string const &rhs);

		void										reset();
};

# include "AMethod.hpp"
# include "Response.hpp"

#endif
