#include "Extension.hpp"

Extension::Extension(void){}

Extension::Extension(Extension const & src)
{
	*this = src;
}

Extension::~Extension(void)
{
	
}

Extension &	Extension::operator=(Extension const & rhs)
{
	if (this == &rhs)
		;
	return *this;
}

std::string
Extension::get_extention(const std::string & path)
{
	size_t posistion = path.rfind(".");

	if (posistion == std::string::npos)
		// throw std::exception();
		return ("");
	return (path.substr(posistion + 1));
}

std::string
Extension::get_mine_type(const std::string & ext )
{
	if (ext == "html")
		return ("text/html");
	else if (ext == "txt")
		return ("text/plain");
	else if (ext == "png")
		return ("image/png");
	else
		return ("application/octet-stream");
}