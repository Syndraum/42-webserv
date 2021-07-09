/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:22:23 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/09 12:02:14 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER
# define SERVER

# include <vector>
# include <map>
# include <list>
# include <utility>
# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <exception>
# include <unistd.h>
# include <cstring>
# include <algorithm>
# include "ServerSocket.hpp"
# include "CGI.hpp"

class CGI;

class Server
{
	public:

		typedef std::map<int, ServerSocket>	port_map;
		typedef std::map<std::string, CGI>	cgi_map;
		typedef std::pair<std::string, CGI>	cgi_pair;

	private:

		std::string							_name;
		port_map							_server_sockets;
		std::string							_root;
		std::list<std::string>				_index;
		bool								_auto_index;
		size_t								_client_max_body_size;
		std::string							_path_error_page;
		cgi_map								_CGI_map;								

	public:

		Server(void);
		Server(std::string const &root, int const port = 8080);
		Server(Server const & src);
		virtual ~Server(void);
		Server &							operator=(Server const &rhs);

		Server &							add_port(int const port);
		Server &							add_index(std::string const & index);
		Server &							add_CGI(std::string name, CGI content);
		void								start(int const worker);

		port_map &						get_server_socket();
		ServerSocket const &				get_server_socket(int port) const;
		const bool	&						get_auto_index() const;

		Server &							set_name(std::string const & name);
		Server &							set_root(std::string const & root);
		Server &							set_auto_index(bool const auto_index);
		Server &							set_client_max_body_size(size_t const limit);
		Server &							set_path_error_page(std::string const & path);
		void								print() const;

};

#endif
