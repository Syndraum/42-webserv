/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerResponse.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:35:11 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 20:26:31 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HandlerResponse.hpp"

HandlerResponse::HandlerResponse(void) : _strategy(0), _response(0) {}

HandlerResponse::HandlerResponse(HandlerResponse const & src)
{
	*this = src;
}

HandlerResponse::~HandlerResponse(void)
{
	reset();
}

HandlerResponse &	HandlerResponse::operator=(HandlerResponse const & rhs)
{
	if (this != &rhs)
		;
	return *this;
}

void
HandlerResponse::set_strategy(IResponseStrategy * strategy)
{
	_strategy = strategy;
}

void
HandlerResponse::do_strategy(Client & client)
{
	_response = _strategy->create(client);
}

void
HandlerResponse::reset()
{
	delete _response;
	_response = 0;
	delete _strategy;
	_strategy = 0;
}