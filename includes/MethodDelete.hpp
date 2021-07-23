/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodDelete.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:16 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:50:17 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODDELETE
# define METHODDELETE

#include "AMethod.hpp"

class MethodDelete : public AMethod
{
	private:

		MethodDelete &		operator=(MethodDelete const &rhs);
		MethodDelete(MethodDelete const & src);

	public:

		MethodDelete(void);
		virtual ~MethodDelete(void);

		virtual void		action(const Request &, Response &);
};

#endif
