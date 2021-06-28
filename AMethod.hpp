#ifndef AMETHOD
# define AMETHOD

# include <string>
# include "Request.hpp"
# include "Response.hpp"
# include <cstdio>
# include <exception>

class AMethod
{
protected:
	AMethod(void);
	AMethod &	operator=(AMethod const &rhs);
	AMethod(AMethod const & src);
	
	std::string	_name;

public:

	AMethod(std::string name);
	virtual ~AMethod(void);

	virtual void	action(const Request &, Response &) = 0;

};

#endif
