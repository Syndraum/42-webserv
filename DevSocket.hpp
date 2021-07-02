/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DevSocket.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:49:49 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:49:51 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cdai - temp file
#ifndef DEVSOCKET
#define DEVSOCKET

#include "ASocket.hpp"

class DevSocket : public ASocket
{
	public:

		DevSocket(void);
		DevSocket(int socket);
		virtual ~DevSocket(void);
};

#endif
