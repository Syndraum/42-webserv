#ifndef STRATEGY_ERROR_HPP
# define STRATEGY_ERROR_HPP

# include "IResponseStrategy.hpp"

class StrategyError : public IResponseStrategy
{
	int	_code;
public:

	StrategyError(int code = 500);
	StrategyError(StrategyError const & src);
	virtual ~StrategyError(void);
	StrategyError &	operator=(StrategyError const &rhs);
	virtual IResponseStrategy *	clone() const;

private:
	virtual Response * create(Client &);
};

#endif
