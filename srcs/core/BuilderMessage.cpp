/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuilderMessage.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:33:55 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 20:24:56 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BuilderMessage.hpp"

BuilderMessage::BuilderMessage(void) : _message(0) {}

BuilderMessage::BuilderMessage(BuilderMessage const & src) : _message(0)
{
	*this = src;
}

BuilderMessage::~BuilderMessage(void)
{
	
}

BuilderMessage &	BuilderMessage::operator=(BuilderMessage const & rhs)
{
	if (this != &rhs)
		_message = rhs._message;
	return *this;
}

void
BuilderMessage::_parse_headers(std::string line)
{
	size_t		len = line.find(": ");
	std::string	key;
	std::string	value;

	if (line.length() == 1 && line[0] == '\r'){
		_message->set_header_lock(true);
	}
	else if (line[line.length() - 1] != '\r' || len == std::string::npos || line[len - 1] == ' ')
		throw BadRequest();
	key = line.substr(0, len);
	if (_message->has_header(key))
		throw BadRequest();
	value = line.substr(len + 2, line.length() - len - 3);
	_message->add_header(key, value);
}

Message *
BuilderMessage::get_message() const
{
	return _message;
}

void
BuilderMessage::set_message(Message * message)
{
	if (!message)
		throw std::exception();
	_message = message;
}
