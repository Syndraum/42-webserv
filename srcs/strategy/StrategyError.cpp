#include "StrategyError.hpp"

StrategyError::StrategyError(int code) : 
IResponseStrategy(),
_code(code)
{}

StrategyError::StrategyError(StrategyError const & src) :
IResponseStrategy()
{
	*this = src;
}

StrategyError::~StrategyError(void)
{
	
}

StrategyError &
StrategyError::operator=(StrategyError const & rhs)
{
	IResponseStrategy::operator=(rhs);
	if (this != &rhs)
		_code = rhs._code;
	return *this;
}

IResponseStrategy *	
StrategyError::clone() const
{
	StrategyError * copy = new StrategyError();
	*copy = *this;
	return (copy);
}

Response * 
StrategyError::create(Client & client)
{
	Response * response = 0;

	(void)client;
	response = new Response();
	response->set_error(_code, client.get_server().get_path_error_page());
	_finish = true;
	return (response);
}