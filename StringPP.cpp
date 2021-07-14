#include "StringPP.hpp"

StringPP::StringPP(void) : m_string(std::string()) {}

StringPP::StringPP(StringPP const & src) : m_string(src.m_string) {}

StringPP::~StringPP(void)
{
	
}

StringPP &
StringPP::operator=(StringPP const & rhs)
{
	if (this != &rhs)
		this->m_string = rhs.m_string;
	return *this;
}

StringPP &
StringPP::operator=(std::string const & rhs)
{
	this->m_string = rhs;
	return *this;
}

std::string &
StringPP::str()
{
	return (this->m_string);
}

std::string &
StringPP::replace_all(const std::string & search, const std::string & replace)
{
	size_t index = 0;

	while (true)
	{
		index = m_string.find(search, index);
		if (index == std::string::npos)
			break;
		m_string.replace(index, search.length(), replace);
		index += replace.length();
	}
	return (m_string);
}
