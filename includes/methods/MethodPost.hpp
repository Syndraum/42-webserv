/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodPost.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:03:22 by cdai              #+#    #+#             */
/*   Updated: 2021/07/28 18:51:00 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHOD_POST_HPP
# define METHOD_POST_HPP

#include "AMethod.hpp"

class MethodPost : public AMethod
{
	private:

		MethodPost &		operator=(MethodPost const &rhs);
		MethodPost(MethodPost const & src);

	public:

		MethodPost(void);
		virtual ~MethodPost(void);

		virtual void		action(const Request &, Response &, Server &);
};

#endif
