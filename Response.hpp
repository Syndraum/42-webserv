/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 12:02:41 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/01 15:44:01 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE
# define RESPONSE

# include <string>
# include <map>
# include <utility>
# include <sstream>

# include <unistd.h>
# include <fstream>
# include "Reader.hpp"
# include "StringPP.hpp"
# include "Info.hpp"

# include <iostream>

class Request;

class Response
{
	public:

		typedef std::map<std::string, std::string>	header_map;

	private:

		std::string									_version;
		int											_code;
		header_map									_headers;
		std::string									_body;
		Request &									_request;
	
		std::string									_1xx__response(int code);
		std::string									_2xx__response(int code);
		std::string									_3xx__response(int code);
		std::string									_4xx__response(int code);
		std::string									_5xx__response(int code);

	public:

		Response(Request &, int code = 200);
		Response(Response const & src);
		virtual ~Response(void);
		Response &									operator=(Response const &rhs);

		template <typename T>
		Response &									add_header(std::string name, T content)
		{
			std::stringstream ss;

			ss << content;
			return (add_header(name, ss.str()));
		}
		Response &									add_header(std::string name, std::string content);
		Response &									clear_header();
		std::string									get_response();
		void										send_response(int fd);
		std::string									get_message(int code);
		Response &									set_code(int code);
		Response &									set_body_from_file(const std::string & filename);
		Response &									set_body(const std::string & body);
		Response &									set_404(std::string & filename);
		Response &									set_error(int code);
};

# include "Request.hpp"

#endif
