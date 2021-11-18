/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyError.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:35:31 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/18 14:35:31 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StrategyError.hpp"

StrategyError::StrategyError(int code) : 
IResponseStrategy(),
_code(code)
{}

StrategyError::StrategyError(StrategyError const & src) :
IResponseStrategy()
{
	*this = src;
}

StrategyError::~StrategyError(void)
{
	
}

StrategyError &
StrategyError::operator=(StrategyError const & rhs)
{
	IResponseStrategy::operator=(rhs);
	if (this != &rhs)
		_code = rhs._code;
	return *this;
}

IResponseStrategy *	
StrategyError::clone() const
{
	StrategyError * copy = new StrategyError();
	*copy = *this;
	return (copy);
}

Response * 
StrategyError::create(Client & client)
{
	Response *	response	= client.get_response();

	if ((client.get_revent() & POLLIN) != 0)
	{
		client.get_socket_struct().get_reader()._reset_buffer();
		return 0;
	}
	if (response == 0)
		response = new Response();
	response->set_error(_code, client.get_server().get_path_error_page());
	_finish = true;
	return (response);
}