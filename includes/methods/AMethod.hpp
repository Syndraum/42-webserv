/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMethod.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:48:57 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/12 16:18:20 by syndraum         ###   ########.fr       */
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
		bool				_finish;

		AMethod(void);
		AMethod(AMethod const & src);

	public:

		AMethod &			operator=(AMethod const &rhs);
		AMethod(std::string name);
		virtual ~AMethod(void);

		const std::string &	get_name() const;
		bool				is_finish() const;
		void				finished();
		virtual void		action(const Request &, Response &, Server &, AReaderFileDescriptor &) = 0;
		virtual AMethod *	clone() const = 0 ;

};

# include "Request.hpp"

#endif
