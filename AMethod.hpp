/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMethod.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:48:57 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:48:58 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMETHOD
# define AMETHOD

# include <string>
# include "Response.hpp"
# include <cstdio>
# include <exception>

class Request;

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
		virtual void		action(const Request &, Response &) = 0;

};

# include "Request.hpp"

#endif
