/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyIndex.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:38:00 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 21:15:02 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
