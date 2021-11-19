/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pipe.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:36:15 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 21:08:16 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE
# define PIPE

#include <vector>

class Pipe
{
	std::vector<int>			_out;
	std::vector<int>			_err;
	std::vector<int>			_in;

public:

	Pipe(void);
	Pipe(Pipe const & src);
	virtual ~Pipe(void);
	Pipe &	operator=(Pipe const &rhs);
	int *	get_out();
	int *	get_err();
	int *	get_in();

};

#endif
