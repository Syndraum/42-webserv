/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyReturn.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:35:39 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 20:09:52 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StrategyReturn.hpp"

StrategyReturn::StrategyReturn(const Redirection & redirection) :
	IResponseStrategy(),
	_redirection(redirection)
{}

StrategyReturn::StrategyReturn(StrategyReturn const & src) :
	IResponseStrategy(),
	_redirection(src._redirection)
{
	*this = src;
}

StrategyReturn::~StrategyReturn(void)
{
	
}

StrategyReturn &
StrategyReturn::operator=(StrategyReturn const & rhs)
{
	IResponseStrategy::operator=(rhs);
	if (this != &rhs)
		;
	return *this;
}

IResponseStrategy *	
StrategyReturn::clone() const
{
	StrategyReturn * copy = new StrategyReturn(_redirection);
	*copy = *this;
	return (copy);
}

Response *
StrategyReturn::create(Client & client)
{
	Response *				response	= client.get_response();
	AReaderFileDescriptor & reader		= client.get_socket_struct().get_reader();

	if (!reader.body_full())
	{
		reader._reset_buffer();
		return 0;
	}
	if (response == 0)
		response = new Response();
	response->set_code(_redirection.get_code());
	if (_redirection.is_handler())
		response->add_header("Location", _redirection.get_ressource());
	_finish = true;
	(void)client;
	return (response);
}