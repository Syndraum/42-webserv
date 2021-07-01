#include "MethodDelete.hpp"

MethodDelete::MethodDelete(void) : AMethod("DELETE") {}

MethodDelete::~MethodDelete(void)
{
	
}

void	MethodDelete::action(const Request & request, Response & response)
{
	if (0 != (std::remove(request.get_path().c_str())))
	{
		response.set_code(404).clear_header();
	}
	else
	{
		response.set_code(204);
	}
}
