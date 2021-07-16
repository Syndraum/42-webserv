#ifndef IRESPONSESTRATEGY
# define IRESPONSESTRATEGY

# include "Response.hpp"
# include "Server.hpp"
# include "Request.hpp"

class IResponseStrategy
{
public:
	virtual Response * create(Server &, Request &) = 0;
};

#endif
