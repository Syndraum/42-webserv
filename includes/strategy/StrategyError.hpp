/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyError.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:37:54 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/18 14:37:55 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
