/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:41:15 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 21:15:19 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <exception>
# include <cstring>
# include <iostream>

class Array
{
	char**		_data;
	size_t		_size;
	size_t		_capacity;

	public:

		Array(void);
		Array(size_t capacity);
		Array(Array const & src);
		virtual ~Array(void);
		Array &	operator=(Array const &rhs);

		void	set_capacity(size_t capacity);
		char ** data() const;
		size_t	size() const;
		static size_t	len(char ** array);
		void	push_back(const char * value);
		void	clear();
};

#endif
