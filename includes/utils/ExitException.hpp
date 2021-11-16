/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExitException.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:41:19 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/16 16:42:13 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_ERROR_HPP
# define EXIT_ERROR_HPP

# include <exception>
# include <iostream>
# include <typeinfo>

class ExitException: public std::exception
{
	virtual const char*	what() const throw(){
		return "Exit exception";
	}
};

#endif