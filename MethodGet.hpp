#ifndef METHODGET
# define METHODGET

# include "AMethod.hpp"

class MethodGet : public AMethod
{
	MethodGet(void);
	MethodGet &	operator=(MethodGet const &rhs);
public:

	MethodGet(MethodGet const & src);
	virtual ~MethodGet(void);

	virtual void action(const Request &, Response &);

private:

};

#endif
