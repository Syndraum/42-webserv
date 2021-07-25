/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodPost.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:03:22 by cdai              #+#    #+#             */
/*   Updated: 2021/07/20 16:08:09 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODPOST
# define METHODPOST

#include "AMethod.hpp"

class MethodPost : public AMethod
{
	private:

		MethodPost &		operator=(MethodPost const &rhs);
		MethodPost(MethodPost const & src);

	public:

		MethodPost(void);
		virtual ~MethodPost(void);

		virtual void		action(const Request &, Response &);
};

#endif
