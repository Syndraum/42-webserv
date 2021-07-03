/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:36 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:50:37 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reader.hpp"

Reader::Reader(void) :
_path(),
_ifs(),
_length()
{}

Reader::Reader(const std::string & path) :
_path(path),
_ifs(),
_length(0)
{}

Reader::Reader(Reader const & src)
{
	*this = src;
}

Reader::~Reader(void) {}

Reader &
Reader::operator=(Reader const & rhs)
{
	if (this != &rhs)
		;
	return *this;
}

void
Reader::open()
{
	_ifs.open(_path.c_str());
	_ifs.seekg (0, _ifs.end);
	_length = _ifs.tellg();
	_ifs.seekg (0, _ifs.beg);
}

void
Reader::to_string(std::string & str)
{
	char * buffer = new char[_length + 1];
	_ifs.read(buffer, _length);
	buffer[_length] = '\0';

	str = std::string(buffer, _length);
	delete[] buffer;
}

void
Reader::close()
{
	_ifs.close();
}

int
Reader::get_length() const
{
	return _length;
}

std::ifstream &
Reader::get_ifs()
{
	return _ifs;
}