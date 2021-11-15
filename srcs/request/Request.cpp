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
	Message(),
	_method(0),
	_path(),
	_uri(),
	_version()
{}

Request::Request(Request const &rhs)
{
	*this = rhs;
}

Request::~Request()
{
	delete (_method);
}

Request const &
Request::operator=(Request const &rhs)
{
	Message::operator=(rhs);
	delete (_method);
	_method = 0;
	if(rhs.get_method())
		_method = rhs.get_method()->clone();
	_path = rhs.get_path();
	_uri = rhs._uri;
	_version = rhs.get_version();
	return (*this);
}

AMethod *
Request::get_method() const
{ return (_method); }

std::string const &
Request::get_path() const
{ return (_path); }

URI &
Request::get_uri()
{ return (_uri); }

const URI &
Request::get_uri() const
{ return (_uri); }

std::string const &
Request::get_version() const
{ return (_version); }

void
Request::set_method(AMethod * rhs)
{ _method = rhs; }

void
Request::set_path(std::string const &rhs)
{ 
	_path = rhs;
}

void
Request::set_uri(std::string const & uri)
{
	_uri.set_uri(uri);
}

void
Request::set_version(std::string const &rhs)
{ _version = rhs; }

// void
// Request::action(Response & response)
// {
// 	if (!_method) //if method == NULL
// 		throw NoMethod();
// 	_method->action(*this, response);
// }

void
Request::reset()
{
	if (_method != 0)
		delete (_method);
	_method = 0;
	_path = "";
	_version = "";
	_headers.clear();
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
