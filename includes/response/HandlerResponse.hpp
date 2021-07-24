#ifndef HANDLERRESPONSE
# define HANDLERRESPONSE

# include "Response.hpp"
# include "IResponseStrategy.hpp"
# include "Client.hpp"
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
	void	do_strategy(Client &);
	void	send(int fd);

private:

};

#endif
