/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:27:00 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/23 12:41:14 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# define GET 0
# define POST 1
# define DELETE 2

# define VERSION "HTTP/1.1"

# include "includes.hpp"

using namespace std;

class Request
{
	private:
		int						_method;
		string					_path;
		string					_version;
		map<string, string>		_headers;

	public:
		Request();
		Request(int method, string const &path, string const &version, map<string, string> const &headers);
		Request(Request const &rhs);
		~Request();
		Request const &operator=(Request const &rhs);

		int							get_method() const;
		string const				&get_path() const;
		string const				&get_version() const;
		map<string, string> const	&get_headers() const;
		string const				&get_header(string const &key);

		void						set_method(int rhs);
		void						set_path(string const &rhs);
		void						set_version(string const &rhs);
		void						set_headers(map<string, string> const &rhs);
		void						add_header(pair<string, string> const &rhs);

		void						print_debug() const;
};

#endif