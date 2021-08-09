/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodDelete.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:12 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:50:14 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MethodDelete.hpp"

MethodDelete::MethodDelete(void) :
AMethod("DELETE")
{}

MethodDelete::~MethodDelete() {}

void
MethodDelete::action(const Request & request, Response & response, Server & server)
{
	if (0 != (std::remove(request.get_path().c_str())))
	{
		response.set_error(404, server.get_path_error_page());
	}
	else
	{
		response.set_code(204);
	}
}
