/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:58:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 21:22:14 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"

void	exit_properly(int)
{
	throw(ExitException());
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

		// sigaction(SIGINT, &sigIntHandler, NULL);
		if (!core.init(argc, argv, env))
			core.start();
	}
	catch (ExitException &e)
	{
		return (0);
	}
}
