/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:27:00 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/24 21:34:07 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# define GET 0
# define POST 1
# define DELETE 2

# define VERSION "HTTP/1.1"

# include "includes.hpp"

class Request
{
	private:
		int						_method;
		std::string					_path;
		std::string					_version;
		std::map<std::string, std::string>		_headers;

	public:
		Request();
		Request(int method, std::string const &path, std::string const &version, std::map<std::string, std::string> const &headers);
		Request(Request const &rhs);
		~Request();
		Request const &operator=(Request const &rhs);

		int							get_method() const;
		std::string const				&get_path() const;
		std::string const				&get_version() const;
		std::map<std::string, std::string> const	&get_headers() const;
		std::string const				&get_header(std::string const &key);

		void						set_method(int rhs);
		void						set_path(std::string const &rhs);
		void						set_version(std::string const &rhs);
		void						set_headers(std::map<std::string, std::string> const &rhs);
		void						add_header(std::pair<std::string, std::string> const &rhs);

		void						print_debug() const;
};

#endif