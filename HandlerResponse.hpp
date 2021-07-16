#ifndef HANDLERRESPONSE
# define HANDLERRESPONSE

# include "Response.hpp"
# include "IResponseStrategy.hpp"
# include "Server.hpp"
# include "Request.hpp"
# include <exception>

class HandlerResponse
{
	IResponseStrategy *		_strategy;
	Response *				_response;
public:

	HandlerResponse(void);
	HandlerResponse(HandlerResponse const & src);
	virtual ~HandlerResponse(void);
	HandlerResponse &	operator=(HandlerResponse const &rhs);

	void	set_strategy(IResponseStrategy *);
	void	do_strategy(Server &, Request &);
	void	send(int fd);

private:

};

#endif
