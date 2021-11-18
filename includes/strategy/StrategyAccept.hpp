/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyAccept.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:37:51 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/18 14:37:52 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	virtual IResponseStrategy *	clone() const;

private:
	virtual Response * create(Client &);
};

#endif
