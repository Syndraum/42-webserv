#include "HandlerResponse.hpp"

HandlerResponse::HandlerResponse(void) : _strategy(0), _response(0) {}

HandlerResponse::HandlerResponse(HandlerResponse const & src)
{
	*this = src;
}

HandlerResponse::~HandlerResponse(void)
{
	
}

HandlerResponse &	HandlerResponse::operator=(HandlerResponse const & rhs)
{
	if (this != &rhs)
		;
	return *this;
}

void
HandlerResponse::set_strategy(IResponseStrategy * strategy)
{
	_strategy = strategy;
}

void
HandlerResponse::do_strategy(Server & server, Request & request)
{
	_response = _strategy->create(server, request);
}

void
HandlerResponse::send(int fd)
{
	if (_response == 0)
		throw std::exception();
	_response->send(fd);
}