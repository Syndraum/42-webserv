/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MethodGet.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:20 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:50:21 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MethodGet.hpp"

MethodGet::MethodGet(void) :
AMethod("GET")
{}

MethodGet::~MethodGet()
{}

void
MethodGet::action(const Request & request, Response & response)
{
	try
	{
		response.set_code(200).set_body(request.get_path().c_str());
	}
	catch(const std::exception& e)
	{
		response.set_code(404).clear_header();
	}
}
