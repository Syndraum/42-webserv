/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMethod.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:48:52 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/12 16:18:26 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMethod.hpp"

AMethod::AMethod(void) :
_name(),
_finish(false)
{}

AMethod::AMethod(std::string name) :
_name(name),
_finish(false)
{}

AMethod::~AMethod(void) {}

AMethod &
AMethod::operator=(AMethod const &rhs)
{
	if (this != &rhs)
	{
		_name = rhs._name;
		_finish = rhs._finish;
	}
	return (*this);
}

const std::string &
AMethod::get_name() const
{
	return (_name);
}

bool
AMethod::is_finish() const
{
	return (_finish);
}

void
AMethod::finished()
{
	_finish = true;
}