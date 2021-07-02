/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:27:00 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 16:49:05 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# define GET 0
# define POST 1
# define DELETE 2

# define VERSION "HTTP/1.1"

# include "Response.hpp"

class AMethod;

class Request
{
	private:
		AMethod	*									_method;
		std::string									_path;
		std::string									_version;
		std::map<std::string, std::string>			_headers;

	public:
		Request();
		Request(Request const &rhs);
		~Request();
		Request const &								operator=(Request const &rhs);

		AMethod *									get_method() const;
		std::string const &							get_path() const;
		std::string const &							get_version() const;
		std::map<std::string, std::string> const &	get_headers() const;
		std::string const &							get_header(std::string const &key);

		void										set_method(AMethod * rhs);
		void										set_path(std::string const &rhs);
		void										set_version(std::string const &rhs);
		void										set_headers(std::map<std::string, std::string> const &rhs);
		void										add_header(std::pair<std::string, std::string> const &rhs);

		void										action(Response &);

//		void										print_debug() const;
};

# include "AMethod.hpp"

#endif
