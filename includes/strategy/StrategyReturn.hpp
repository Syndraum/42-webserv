/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyReturn.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:38:06 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/18 14:38:06 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	virtual IResponseStrategy *	clone() const;

private:
	virtual Response *	create(Client &);
};

#endif
