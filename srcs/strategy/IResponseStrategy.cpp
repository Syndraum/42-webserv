#include "IResponseStrategy.hpp"

IResponseStrategy::IResponseStrategy() :
_finish(false)
{

}

IResponseStrategy::IResponseStrategy(IResponseStrategy const & src) : 
_finish(src._finish)
{

}

IResponseStrategy &
IResponseStrategy::operator=(IResponseStrategy const &rhs)
{
	if (this != &rhs)
	{
		_finish = rhs._finish;
	}
	return (*this);
}

bool
IResponseStrategy::is_finish() const
{
	return (_finish);
}