#ifndef STRINGPP
# define STRINGPP

#include <string>
#include <sstream>

class StringPP
{
	std::string m_string;
public:

	StringPP(void);
	StringPP(StringPP const & src);
	virtual ~StringPP(void);
	StringPP &	operator=(StringPP const &rhs);
	StringPP &	operator=(std::string const &rhs);

	std::string &	str();
	template <typename T>
	std::string &	replace_all(const std::string & search, T & replace)
	{
		std::stringstream ss;

		ss << replace;
		replace_all(search, ss.str());
		return (m_string);
	}
	std::string &	replace_all(const std::string & search, const std::string & replace);

};

#endif
