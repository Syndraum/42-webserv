#include "StrategyError.hpp"

StrategyError::StrategyError(int code) : _code(code)
{}

StrategyError::StrategyError(StrategyError const & src)
{
	*this = src;
}

StrategyError::~StrategyError(void)
{
	
}

StrategyError &
StrategyError::operator=(StrategyError const & rhs)
{
	if (this != &rhs)
		_code = rhs._code;
	return *this;
}

Response * 
StrategyError::create(Server & server, Request & request)
{
	Response * response = 0;

	(void)server;
	(void)request;
	response = new Response();
	response->set_error(_code);
	return (response);
}