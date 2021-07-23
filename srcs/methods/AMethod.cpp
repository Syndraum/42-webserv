/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMethod.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:48:52 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:48:54 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMethod.hpp"

AMethod::AMethod(void) :
_name()
{}

AMethod::AMethod(std::string name) :
_name(name)
{}

AMethod::~AMethod(void) {}

const std::string &
AMethod::get_name() const
{
	return (_name);
}
