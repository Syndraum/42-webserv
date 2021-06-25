/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:28:56 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/23 12:41:06 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

using namespace std;

Request::Request()
{}

Request::Request(int method, string const &path, string const &version, map<string, string> const &headers)
: _method(method), _path(path), _version(version), _headers(headers)
{}

Request::Request(Request const &rhs)
{
	*this = rhs;
}

Request::~Request()
{}

Request const 				&Request::operator=(Request const &rhs)
{
	_method = rhs.get_method();
	_path = rhs.get_path();
	_version = rhs.get_version();
	_headers = rhs.get_headers();
	return (*this);
}

int							Request::get_method() const { return (_method); }
string const				&Request::get_path() const { return (_path); }
string const				&Request::get_version() const { return (_version); }
map<string, string> const	&Request::get_headers() const { return (_headers); }
string const				&Request::get_header(string const &key) { return (_headers[key]); }

void						Request::set_method(int rhs){ _method = rhs; }
void						Request::set_path(string const &rhs){ _path = rhs; }
void						Request::set_version(string const &rhs){ _version = rhs; }
void						Request::set_headers(map<string, string> const &rhs){ _headers = rhs; }
void						Request::add_header(pair<string, string> const &rhs){ _headers.insert(rhs); }

void						Request::print_debug() const //TMP
{
	cerr << "METHOD CODE : " << _method << " PATH : \"" << _path << "\" " << _version << endl;
    cerr << "HEADERS : " << endl;

    for (auto& it: _headers)
        cout << "\"" << it.first << "\" - \"" << it.second << "\"" << endl;

}
