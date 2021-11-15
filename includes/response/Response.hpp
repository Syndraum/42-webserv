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

		enum response_state {
			WRITE_HEADER,
			WRITE_BODY,
			END
		};

		typedef std::map<std::string, std::string>	header_map;

	private:

		std::string									_version;
		int											_code;
		response_state								_state;
		Reader										_file_reader;

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

		std::string									get_header();
		std::string									get_response();
		void										send_header(int fd);
		void										send_body(int fd);
		std::string									get_message(int code);
		Response &									set_code(int code);
		Response &									set_body_from_file(const std::string & filename);
		Response &									set_filename(const std::string & filename);
		Response &									set_error(int code, std::string const & path_error);
		int											get_code() const;
		response_state								get_state() const;
};

# include "Request.hpp"

#endif
