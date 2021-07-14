/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:28:56 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/02 15:53:14 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request():
_method(0),
_path(),
_version(),
_headers(),
_is_first_line(true),
_uri()
{}

Request::Request(Request const &rhs)
{
	*this = rhs;
}

Request::~Request() {}

Request const &
Request::operator=(Request const &rhs)
{
	_method = rhs.get_method();
	_path = rhs.get_path();
	_version = rhs.get_version();
	_headers = rhs.get_headers();
	_is_first_line = rhs._is_first_line;
	_uri = rhs._uri;
	return (*this);
}

AMethod *
Request::get_method() const
{ return (_method); }

std::string const &
Request::get_path() const
{ return (_path); }

std::string const &
Request::get_version() const
{ return (_version); }

std::map<std::string, std::string> const &
Request::get_headers() const
{ return (_headers); }

std::string const &
Request::get_header(std::string const &key)
{ return (_headers[key]); }

bool
Request::get_first_line() const
{ return (_is_first_line); }

void
Request::set_method(AMethod * rhs)
{ _method = rhs; }

void
Request::set_path(std::string const &rhs)
{ 
	_path = rhs;
	_uri.set_uri(rhs);
}

void
Request::set_version(std::string const &rhs)
{ _version = rhs; }

void
Request::set_headers(std::map<std::string, std::string> const &rhs)
{ _headers = rhs; }

void
Request::add_header(std::pair<std::string, std::string> const &rhs)
{ _headers.insert(rhs); }

void
Request::set_first_line(bool last_line)
{ _is_first_line = last_line; }

void
Request::action(Response & response)
{
	if (!_method) //if method == NULL
		throw NoMethod();
	_method->action(*this, response);
}

void
Request::reset()
{
	_method = 0;
	_path = "";
	_version = "";
	_headers.clear();
	_is_first_line  = true;
}

//void
//Request::print_debug() const //TMP
//{
//	cerr << "METHOD CODE : " << _method << " PATH : \"" << _path << "\" " << _version << endl;
//    cerr << "HEADERS : " << endl;
//
//    for (auto& it: _headers)
//        cout << "\"" << it.first << "\" - \"" << it.second << "\"" << endl;
//
//}
