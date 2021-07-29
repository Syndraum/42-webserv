#ifndef IRESPONSE_STRATEGY_HPP
# define IRESPONSE_STRATEGY_HPP

# include "Client.hpp"
# include "Response.hpp"
# include "Server.hpp"
# include "Request.hpp"

class IResponseStrategy
{
public:
	virtual Response * create(Client &) = 0;
};

#endif
