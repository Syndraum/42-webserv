#include "MethodGet.hpp"

MethodGet::MethodGet(void) : AMethod("GET") {}


MethodGet::~MethodGet(void)
{
	
}

void	MethodGet::action(const Request & request, Response & response)
{	try
	{
		response.set_code(200).set_body(request.get_path().c_str());
	}
	catch(const std::exception& e)
	{
		response.set_code(404).clear_header();
	}
}
