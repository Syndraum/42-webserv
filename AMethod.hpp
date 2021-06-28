#ifndef AMETHOD
# define AMETHOD

# include <string>
# include "Request.hpp"
# include "Response.hpp"
# include <cstdio>
# include <exception>

class AMethod
{
	AMethod &	operator=(AMethod const &rhs);
	AMethod(AMethod const & src);
	
	std::string	_name;

public:

	AMethod(void);
	virtual ~AMethod(void);

	virtual void	action(const Request &, Response &) const = 0;

};

#endif
