#include "StrategyAccept.hpp"

StrategyAccept::StrategyAccept(void){}

StrategyAccept::StrategyAccept(StrategyAccept const & src)
{
	*this = src;
}

StrategyAccept::~StrategyAccept(void)
{
	
}

StrategyAccept &	StrategyAccept::operator=(StrategyAccept const & rhs)
{
	if (this != &rhs)
		;
	return *this;
}

Response * 
StrategyAccept::create(Client & client)
{
	Response *	response	= 0;
	Request &	request		= client.get_request();
	Server &	server		= client.get_server();

	response = new Response();
	request.set_path(server.get_full_path(request.get_path()));
	request.action(*response);
	return (response);
}
