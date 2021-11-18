/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResponseStrategy.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:37:48 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/18 14:37:48 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESPONSE_STRATEGY_HPP
# define IRESPONSE_STRATEGY_HPP

# include "Client.hpp"
# include "Response.hpp"
# include "Server.hpp"
# include "Request.hpp"
# include "poll.h"

class Client;

class IResponseStrategy
{
protected:
	bool		_finish;

	IResponseStrategy();
	IResponseStrategy(IResponseStrategy const & src);
	IResponseStrategy &			operator=(IResponseStrategy const &rhs);
public:
	virtual ~IResponseStrategy() {}
	virtual Response * create(Client &) = 0;
	bool	is_finish() const;
	virtual IResponseStrategy *	clone() const = 0;
};

#endif
