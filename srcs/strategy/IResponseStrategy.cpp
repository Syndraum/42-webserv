/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResponseStrategy.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:35:22 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 21:21:05 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IResponseStrategy.hpp"

IResponseStrategy::IResponseStrategy() :
_finish(false)
{}

IResponseStrategy::IResponseStrategy(IResponseStrategy const & src) : 
_finish(src._finish)
{}

IResponseStrategy &
IResponseStrategy::operator=(IResponseStrategy const &rhs)
{
	if (this != &rhs)
	{
		_finish = rhs._finish;
	}
	return (*this);
}

bool
IResponseStrategy::is_finish() const
{
	return (_finish);
}