/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMethod.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:48:57 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/28 18:50:24 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMETHOD_HPP
# define AMETHOD_HPP

# include <string>
# include "Server.hpp"
# include "Response.hpp"
# include <cstdio>
# include <exception>
# include "Extension.hpp"
# include "AReaderFileDescriptor.hpp"

class Request;
class Server;

class AMethod
{
	protected:
	
		std::string			_name;

		AMethod(void);
		AMethod(AMethod const & src);
		AMethod &			operator=(AMethod const &rhs);

	public:

		AMethod(std::string name);
		virtual ~AMethod(void);

		const std::string &	get_name() const;
		virtual void		action(const Request &, Response &, Server &, AReaderFileDescriptor &) = 0;

};

# include "Request.hpp"

#endif
