#include "Redirection.hpp"

Redirection::Redirection(int code, const std::string & ressource) :
	_code(code),
	_ressource(ressource)
{}

Redirection::Redirection(Redirection const & src)
{
	*this = src;
}

Redirection::~Redirection(void)
{
	
}

Redirection &
Redirection::operator=(Redirection const & rhs)
{
	if (this != &rhs)
	{
		this->_code = rhs._code;
		this->_ressource = rhs._ressource;
	}
	return *this;
}

bool
Redirection::is_handler() const
{
	if (_code == 307)
		return (true);
	else if (_code >= 301 && _code <= 303)
		return (true);
	return (false);
}

int
Redirection::get_code() const
{
	return (_code);
}

const std::string &
Redirection::get_ressource() const
{
	return (_ressource);
}