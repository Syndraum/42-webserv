#include "StrategyIndex.hpp"

StrategyIndex::StrategyIndex(void){}

StrategyIndex::StrategyIndex(StrategyIndex const & src)
{
	*this = src;
}

StrategyIndex::~StrategyIndex(void)
{
	
}

StrategyIndex &	StrategyIndex::operator=(StrategyIndex const & rhs)
{
	if (this != &rhs)
		;
	return *this;
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
	return (response);
}