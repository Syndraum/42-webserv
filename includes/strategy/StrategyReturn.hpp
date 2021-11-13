#ifndef STRATEGYRETURN
# define STRATEGYRETURN

# include "IResponseStrategy.hpp"
# include "Redirection.hpp"

class StrategyReturn : public IResponseStrategy
{
	const Redirection & _redirection;
	StrategyReturn(void);
public:

	StrategyReturn(const Redirection &);
	StrategyReturn(StrategyReturn const & src);
	virtual ~StrategyReturn(void);
	StrategyReturn &	operator=(StrategyReturn const &rhs);
	IResponseStrategy *	clone() const;

private:
	virtual Response *	create(Client &);
};

#endif
