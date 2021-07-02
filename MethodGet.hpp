/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodGet.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:24 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:50:25 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODGET
# define METHODGET

# include "AMethod.hpp"

class MethodGet : public AMethod
{
	private:

		MethodGet &	operator=(MethodGet const & rhs);
		MethodGet(MethodGet const & src);
		
	public:

		MethodGet(void);
		virtual ~MethodGet(void);

		virtual void action(const Request &, Response &);
};

#endif
