/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyIndex.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:35:36 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 21:21:32 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StrategyIndex.hpp"

StrategyIndex::StrategyIndex(void) :
IResponseStrategy()
{}

StrategyIndex::StrategyIndex(StrategyIndex const & src) :
IResponseStrategy()
{
	*this = src;
}

StrategyIndex::~StrategyIndex(void)
{}

StrategyIndex &	StrategyIndex::operator=(StrategyIndex const & rhs)
{
	IResponseStrategy::operator=(rhs);
	if (this != &rhs)
		;
	return *this;
}

IResponseStrategy *	
StrategyIndex::clone() const
{
	StrategyIndex * copy = new StrategyIndex();
	*copy = *this;
	return (copy);
}

Response * 
StrategyIndex::create(Client & client)
{
	Request	&				request		= client.get_request();
	Server &				server		= client.get_server();
	Response *				response	= client.get_response();
	AReaderFileDescriptor & reader		= client.get_socket_struct().get_reader();

	if (!reader.body_full())
	{
		reader._reset_buffer();
		return 0;
	}
	if (response == 0)
		response = new Response();
	response
		->set_code(200)
		.set_body(server.get_index_page(request))
		.add_header("Content-type", "text/html");
	_finish = true;
	return (response);
}