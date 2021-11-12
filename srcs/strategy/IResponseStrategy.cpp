#include "IResponseStrategy.hpp"

IResponseStrategy::IResponseStrategy() :
_finish(false)
{

}

bool
IResponseStrategy::is_finish() const
{
	return (_finish);
}