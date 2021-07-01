/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodLibrary.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:31 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:50:32 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHODLIBRARY
# define METHODLIBRARY

# include <vector>
# include "AMethod.hpp"

class MethodLibrary
{
	private:

		std::vector<AMethod *>	_methods;

		MethodLibrary(MethodLibrary const & src);
		MethodLibrary &			operator=(MethodLibrary const &rhs);

	public:

		MethodLibrary(void);
		virtual ~MethodLibrary(void);

		MethodLibrary &			add_method(AMethod *);
		AMethod	*				get_method(const std::string &) const;
};

#endif
