#ifndef STRATEGY_CGI_HPP
# define STRATEGY_CGI_HPP

# include "IResponseStrategy.hpp"
# include "RequestCGI.hpp"
# include "CGI.hpp"
# include "Info.hpp"
# include "ReaderFileDescriptor.hpp"
# include "HandlerResponseCGI.hpp"

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
	IResponseStrategy *	clone() const;

private:
	virtual Response *	create(Client &);
	void				_prepare(Client &);
	void				handle_status(const Message &, Response &, Server & server);

};

#endif
