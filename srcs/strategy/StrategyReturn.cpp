#include "StrategyReturn.hpp"

StrategyReturn::StrategyReturn(const Redirection & redirection) :
	IResponseStrategy(),
	_redirection(redirection)
{}

StrategyReturn::StrategyReturn(StrategyReturn const & src) :
	IResponseStrategy(),
	_redirection(src._redirection)
{
	*this = src;
}

StrategyReturn::~StrategyReturn(void)
{
	
}

StrategyReturn &
StrategyReturn::operator=(StrategyReturn const & rhs)
{
	IResponseStrategy::operator=(rhs);
	if (this != &rhs)
		;
	return *this;
}

IResponseStrategy *	
StrategyReturn::clone() const
{
	StrategyReturn * copy = new StrategyReturn(_redirection);
	*copy = *this;
	return (copy);
}

Response *
StrategyReturn::create(Client & client)
{
	Response *	response	= 0;

	(void)client;
	response = new Response();
	response->set_code(_redirection.get_code());
	if (_redirection.is_handler())
		response->add_header("Location", _redirection.get_ressource());
	_finish = true;
	return (response);
}