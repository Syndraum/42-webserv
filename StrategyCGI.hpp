/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyCGI.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 11:33:16 by cdai              #+#    #+#             */
/*   Updated: 2021/07/22 16:47:31 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRATEGYCGI
# define STRATEGYCGI

# include "IResponseStrategy.hpp"
# include "Server.hpp"
# include "Request.hpp"

class StrategyCGI : public IResponseStrategy
{
public:
	StrategyCGI(void);
	StrategyCGI(StrategyCGI const & src);
	virtual ~StrategyCGI(void);
	StrategyCGI &	operator=(StrategyCGI const &rhs);

private:
	virtual Response * create(Server &, Request &);
};

#endif
