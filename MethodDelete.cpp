#include "MethodDelete.hpp"

MethodDelete::MethodDelete(void){}

MethodDelete::MethodDelete(MethodDelete const & src)
{
	*this = src;
}

MethodDelete::~MethodDelete(void)
{
	
}

MethodDelete &	MethodDelete::operator=(MethodDelete const & rhs)
{
	return *this;
}

void	MethodDelete::action(const Request & request, Response & response) const
{
	if (0 != (std::remove(request.get_path().data())))
	{
		response.setCode(404).clearHeader();
	}
	else
	{
		response.setCode(204);
	}
}
