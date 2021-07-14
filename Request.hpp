/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:27:00 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/02 15:51:43 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <map>
# include <string>
# include "URI.hpp"

class AMethod;
class Response;

class Request
{
	private:
		AMethod	*									_method;
		std::string									_path;
		std::string									_version;
		std::map<std::string, std::string>			_headers;
		bool										_is_first_line;
		URI											_uri;

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
		std::string const &							get_version() const;
		std::map<std::string, std::string> const &	get_headers() const;
		std::string const &							get_header(std::string const &key);
		bool										get_first_line() const;

		void										set_method(AMethod * rhs);
		void										set_path(std::string const &rhs);
		void										set_uri(std::string const &rhs);
		void										set_version(std::string const &rhs);
		void										set_headers(std::map<std::string, std::string> const &rhs);
		void										add_header(std::pair<std::string, std::string> const &rhs);
		void										set_first_line(bool);

		void										action(Response &);
		void										reset();

//		void										print_debug() const;
};

# include "AMethod.hpp"
# include "Response.hpp"

#endif
