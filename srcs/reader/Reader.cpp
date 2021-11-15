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
	{
		_ifs.copyfmt(rhs._ifs);
		_path = rhs._path;
		_length = rhs._length;
		_line = rhs._line;
	}
	return *this;
}

void
Reader::open()
{
	if (_ifs.is_open())
		close();
	_ifs.open(_path.c_str(), std::ios_base::in );
	if (_ifs.fail())
		throw std::exception();
	_ifs.seekg (0, _ifs.end);
	_length = _ifs.tellg();
	_ifs.seekg (0, _ifs.beg);
}

void
Reader::set_length()
{
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

void
Reader::get_line()
{
	std::getline(_ifs, _line);
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

std::string
Reader::get_buffer()
{
	char * buffer = new char[BUFFER_SIZE];
	_ifs.read(buffer, BUFFER_SIZE);
	// buffer[BUFFER_SIZE] = '\0';
	std::streamsize nb_char_readed = _ifs.gcount();

	// if (nb_char_readed == 0)
	// {
	// 	std::cout << "nb_char_readed :" << nb_char_readed << std::endl;
	// }
	std::string str(buffer, (std::size_t)nb_char_readed);
	delete[] buffer;
	return str;
}

bool
Reader::finished() const
{
	return _ifs.eof();
}