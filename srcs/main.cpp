/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:58:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/15 19:09:13 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"

class ExitError: public std::exception
{
	virtual const char*	what() const throw(){
		return "Exit error";
	}
};

void	exit_properly(int)
{
	throw(ExitError());
}

int		main(int argc, char *argv[], char *env[])
{
	try
	{
		Core core = Core();
		struct sigaction sigIntHandler;

		sigIntHandler.sa_handler = exit_properly;
		sigemptyset(&sigIntHandler.sa_mask);
		sigIntHandler.sa_flags = 0;

		sigaction(SIGINT, &sigIntHandler, NULL);
		if (!core.init(argc, argv, env))
			core.start();
	}
	catch (ExitError &e)
	{
		class MyError: public std::exception
		{
			virtual const char*	what() const throw(){
				return "My error";
			}
		};
	}
	// while (1)
	// 	;
}
