#ifndef METHODDELETE
# define METHODDELETE

#include "AMethod.hpp"

class MethodDelete : public AMethod
{
	MethodDelete(MethodDelete const & src);
	MethodDelete &	operator=(MethodDelete const &rhs);
public:

	MethodDelete(void);
	virtual ~MethodDelete(void);

	virtual void action(const Request &, Response &) const;

private:

};

#endif
