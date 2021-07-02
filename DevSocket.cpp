/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DevSocket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:49:43 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:49:44 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cdai - temp file
#include "DevSocket.hpp"

DevSocket::DevSocket(void)
{
	_socket = 0;
}

DevSocket::DevSocket(int socket)
{
	_socket = socket;
}

DevSocket::~DevSocket(void) {}
