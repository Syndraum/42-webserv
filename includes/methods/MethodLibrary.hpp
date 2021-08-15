/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodLibrary.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:31 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/28 18:50:52 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef METHOD_LIBRARY_HPP
# define METHOD_LIBRARY_HPP

# include <vector>
# include "AMethod.hpp"

class MethodLibrary
{
	public:
		typedef std::vector<AMethod *>	vector_method;
	private:

		vector_method	_methods;

		MethodLibrary(MethodLibrary const & src);
		MethodLibrary &			operator=(MethodLibrary const &rhs);

	public:

		MethodLibrary(void);
		virtual ~MethodLibrary(void);

		MethodLibrary &			add_method(AMethod *);
		AMethod	*				get_method(const std::string &) const;
		const vector_method &	get_vector() const;
};

#endif
