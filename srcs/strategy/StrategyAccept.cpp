#include "StrategyAccept.hpp"

StrategyAccept::StrategyAccept(void) :
IResponseStrategy()
{}

StrategyAccept::StrategyAccept(StrategyAccept const & src) :
IResponseStrategy()
{
	*this = src;
}

StrategyAccept::~StrategyAccept(void)
{
	
}

StrategyAccept &	StrategyAccept::operator=(StrategyAccept const & rhs)
{
	IResponseStrategy::operator=(rhs);
	if (this != &rhs){
		;
	}
	return *this;
}

IResponseStrategy *	
StrategyAccept::clone() const
{
	StrategyAccept * copy = new StrategyAccept();
	*copy = *this;
	return (copy);
}

Response * 
StrategyAccept::create(Client & client)
{
	// std::cout << "BEGIN" << std::endl;
	Response *				response	= client.get_response();
	Request &				request		= client.get_request();
	Server &				server		= client.get_server();
	AReaderFileDescriptor &	reader		= client.get_socket_struct().get_reader();

	// std::cout << "ACCEPT" << std::endl;
	if (response == 0){
		response = new Response();
		request.set_path(server.get_full_path(request.get_path()));
	}
	request.get_method()->action(request, *response, server, reader);
	if (request.get_method()->is_finish())
		_finish = true;
	return (response);
}