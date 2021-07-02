/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodLibrary.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:27 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:50:28 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MethodLibrary.hpp"

MethodLibrary::MethodLibrary(void) {}

MethodLibrary::~MethodLibrary() {}

MethodLibrary &
MethodLibrary::add_method(AMethod * method)
{
	_methods.push_back(method);
	return *this;
}

AMethod	*
MethodLibrary::get_method(const std::string & name) const
{
	std::vector<AMethod *>::const_iterator ite = _methods.end();
	for (std::vector<AMethod *>::const_iterator it = _methods.begin(); it != ite; it++)
	{
		if ((*it)->get_name() == name)
			return (*it);
	}
	return (0);
}
