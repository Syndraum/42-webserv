/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:58:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/08 16:02:34 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"

int		main(int argc, char *argv[], char *env[])
{
	Core core = Core();

	if (!core.init(argc, argv, env))
		core.start();
	core.clean();
	// while (1)
	// 	;
}
