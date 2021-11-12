#ifndef IRESPONSE_STRATEGY_HPP
# define IRESPONSE_STRATEGY_HPP

# include "Client.hpp"
# include "Response.hpp"
# include "Server.hpp"
# include "Request.hpp"

class Client;

class IResponseStrategy
{
protected:
	bool		_finish;

	IResponseStrategy();
	IResponseStrategy &			operator=(IResponseStrategy const &rhs);
public:
	virtual ~IResponseStrategy() {}
	virtual Response * create(Client &) = 0;
	bool	is_finish() const;
};

#endif
