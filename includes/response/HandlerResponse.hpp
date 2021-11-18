/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandlerResponse.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:37:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/18 14:37:41 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_RESPONSE_HPP
# define HANDLER_RESPONSE_HPP

# include "Response.hpp"
# include "IResponseStrategy.hpp"
# include "Client.hpp"
# include <exception>

class HandlerResponse
{
	IResponseStrategy *		_strategy;
	Response *				_response;
public:

	HandlerResponse(void);
	HandlerResponse(HandlerResponse const & src);
	virtual ~HandlerResponse(void);
	HandlerResponse &	operator=(HandlerResponse const &rhs);

	void	set_strategy(IResponseStrategy *);
	void	do_strategy(Client &);
	void	send(int fd);
	void	reset();

private:

};

#endif
