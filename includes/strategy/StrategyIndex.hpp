#ifndef STRATEGY_INDEX_HPP
# define STRATEGY_INDEX_HPP

# include "IResponseStrategy.hpp"

class StrategyIndex : public IResponseStrategy
{
public:

	StrategyIndex(void);
	StrategyIndex(StrategyIndex const & src);
	virtual ~StrategyIndex(void);
	StrategyIndex &	operator=(StrategyIndex const &rhs);
	IResponseStrategy *	clone() const;

private:
	virtual Response * create(Client &);
};

#endif
