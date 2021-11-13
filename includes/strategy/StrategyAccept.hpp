#ifndef STRATEGY_ACCEPT_HPP
# define STRATEGY_ACCEPT_HPP

# include "IResponseStrategy.hpp"
# include "CGI.hpp"

class StrategyAccept : public IResponseStrategy
{
public:

	StrategyAccept(void);
	StrategyAccept(StrategyAccept const & src);
	virtual ~StrategyAccept(void);
	StrategyAccept &	operator=(StrategyAccept const &rhs);
	IResponseStrategy *	clone() const;

private:
	virtual Response * create(Client &);
};

#endif
