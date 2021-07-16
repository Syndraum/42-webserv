#ifndef STRATEGYINDEX
# define STRATEGYINDEX

# include "IResponseStrategy.hpp"

class StrategyIndex : public IResponseStrategy
{
public:

	StrategyIndex(void);
	StrategyIndex(StrategyIndex const & src);
	virtual ~StrategyIndex(void);
	StrategyIndex &	operator=(StrategyIndex const &rhs);

private:
	virtual Response * create(Server &, Request &);
};

#endif
