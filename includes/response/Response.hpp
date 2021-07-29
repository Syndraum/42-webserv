/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:02:41 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/28 18:53:09 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Message.hpp"
# include <sstream>

# include <unistd.h>
# include <fstream>
# include "Reader.hpp"
# include "StringPP.hpp"
# include "Info.hpp"

# include <iostream>

class Request;

class Response : public Message
{
	public:

		typedef std::map<std::string, std::string>	header_map;

	private:

		std::string									_version;
		int											_code;

		std::string									_1xx__response(int code);
		std::string									_2xx__response(int code);
		std::string									_3xx__response(int code);
		std::string									_4xx__response(int code);
		std::string									_5xx__response(int code);

	public:
		Response(int code = 200);
		Response(Response const & src);
		virtual ~Response(void);
		Response &									operator=(Response const &rhs);

		std::string									get_response();
		void										send(int fd);
		std::string									get_message(int code);
		Response &									set_code(int code);
		Response &									set_body_from_file(const std::string & filename);
		Response &									set_error(int code);
		int											get_code() const;
};

# include "Request.hpp"

#endif
