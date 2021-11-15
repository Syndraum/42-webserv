#include "StrategyIndex.hpp"

StrategyIndex::StrategyIndex(void) :
IResponseStrategy()
{}

StrategyIndex::StrategyIndex(StrategyIndex const & src) :
IResponseStrategy()
{
	*this = src;
}

StrategyIndex::~StrategyIndex(void)
{
	
}

StrategyIndex &	StrategyIndex::operator=(StrategyIndex const & rhs)
{
	IResponseStrategy::operator=(rhs);
	if (this != &rhs)
		;
	return *this;
}

IResponseStrategy *	
StrategyIndex::clone() const
{
	StrategyIndex * copy = new StrategyIndex();
	*copy = *this;
	return (copy);
}

Response * 
StrategyIndex::create(Client & client)
{
	Response *	response	= 0;
	Request	&	request		= client.get_request();
	Server &	server		= client.get_server();


	response = new Response();
	response
		->set_code(200)
		.set_body(server.get_index_page(request))
		.add_header("Content-type", "text/html");
	_finish = true;
	return (response);
}