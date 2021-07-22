#ifndef STRATEGYACCEPT
# define STRATEGYACCEPT

# include "IResponseStrategy.hpp"
# include "CGI.hpp"

class StrategyAccept : public IResponseStrategy
{
public:

	StrategyAccept(void);
	StrategyAccept(StrategyAccept const & src);
	virtual ~StrategyAccept(void);
	StrategyAccept &	operator=(StrategyAccept const &rhs);

private:
	virtual Response * create(Server &, Request &);
};

#endif
