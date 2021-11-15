/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodPost.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 16:03:22 by cdai              #+#    #+#             */
/*   Updated: 2021/11/12 19:42:39 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHOD_POST_HPP
# define METHOD_POST_HPP

#include "AMethod.hpp"
#include "Upload.hpp"

class MethodPost : public AMethod
{
	private:

		Upload	_uploader;

		MethodPost &		operator=(MethodPost const &rhs);
		MethodPost(MethodPost const & src);

	public:

		MethodPost(void);
		virtual ~MethodPost(void);

		virtual void		action(const Request &, Response &, Server &, AReaderFileDescriptor &);
		virtual AMethod*	clone() const;
		bool				has_upload(const Request &);
};

#endif
