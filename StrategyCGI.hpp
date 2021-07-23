#ifndef STRATEGYCGI
# define STRATEGYCGI

# include "IResponseStrategy.hpp"
# include "RequestCGI.hpp"
# include "CGI.hpp"
# include "Info.hpp"

class StrategyCGI : public IResponseStrategy
{
	CGI &		_cgi;
	RequestCGI	_request;

	StrategyCGI(void);

public:
	StrategyCGI(CGI &);
	StrategyCGI(StrategyCGI const & src);
	virtual ~StrategyCGI(void);
	StrategyCGI &	operator=(StrategyCGI const &rhs);

private:
	virtual Response *	create(Server &, Request &);
	void				_prepare(Server &, Request &);

};

#endif
