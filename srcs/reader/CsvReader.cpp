/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CsvReader.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:34:41 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/18 14:34:41 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CsvReader.hpp"

CsvReader::CsvReader(void) : Reader() {}

CsvReader::CsvReader(const std::string & path) : Reader(path) {}

CsvReader::CsvReader(CsvReader const & src) : Reader()
{
	*this = src;
}

CsvReader::~CsvReader(void)
{

}

CsvReader &
CsvReader::operator=(CsvReader const & rhs)
{
	if (this != &rhs)
		;
	return *this;
}

bool
CsvReader::has_category(const std::string & category) const
{
	vector::const_iterator	ite = _categories.end();

	for (vector::const_iterator it = _categories.begin(); it != ite; it++)
	{
		if (*it == category)
			return true;
	}
	return false;
}

CsvReader &
CsvReader::set_key_name(const std::string & key)
{

	if (_categories.empty())
		throw std::exception();
	if (!_content.empty())
		throw std::exception();
	if (!has_category(key))
		throw std::exception();
	_key_name = key;
	return (*this);
}

CsvReader &
CsvReader::parse_categeries()
{
	std::string world;

	if (!_categories.empty())
		throw std::exception();
	get_line();
	std::stringstream _s_stream(_line);
	while (std::getline(_s_stream, world, ',')){
		_categories.push_back(world);
	}
	return (*this);
}

CsvReader &
CsvReader::parse_content()
{
	std::string			world;
	std::string			key;
	vector				tmp_vector;
	vector::iterator	it;
	size_t				find;

	if (_categories.empty())
		throw std::exception();
	if (_key_name.empty())
		throw std::exception();
	while (std::getline(_ifs, _line))
	{
		tmp_vector = vector();
		it = _categories.begin();
		find = _line.find('\r');
		if (find != std::string::npos)
			_line.erase(find, 1);
		std::stringstream _s_stream(_line);
		while (std::getline(_s_stream, world, ',')){
			if (*it == _key_name)
				key = world;
			else
				tmp_vector.push_back(world);
			it++;
		}
		_content.insert(std::pair< std::string, vector >(key, tmp_vector));
		tmp_vector.clear();
	}
	return (*this);
}

std::string
CsvReader::operator[](const std::string & key) const
{
	try
	{
		return (_content.at(key).at(0));
	}
	catch (std::exception& e)
	{
		try
		{
			ExitException	&e_exit = dynamic_cast<ExitException&>(e);
			(void)e_exit;
			throw (ExitException());
		}
		catch (std::bad_cast &bc)
		{
			return ("");
		}
	}
}

void
CsvReader::debug() const
{
	for (size_t i = 0; i < _categories.size(); i++)
	{
		std::cout << _categories.at(i) << "\t" << std::flush;
	}
	std::cout << std::endl;
	for (map::const_iterator it = _content.begin(); it != _content.end(); it++)
	{
		std::cout << _key_name << " : " << it->first << " | ";
		for (size_t i = 0; i < it->second.size(); i++)
		{
			std::cout <<it->second[i] << "\t";
		}
		std::cout << std::endl;
	}
}
