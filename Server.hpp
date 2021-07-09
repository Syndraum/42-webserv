/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:22:23 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/01 15:39:57 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER
# define SERVER

# include <vector>
# include <map>
# include <utility>
# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <exception>
# include "ServerSocket.hpp"
# include "unistd.h"
# include "cstring"
# include <algorithm>

class Server
{
	public:

		typedef std::map<int, ServerSocket>	port_vector;

	private:

		std::string							_name;
		port_vector							_server_sockets;
		std::string							_root;
		bool								_auto_index;
		size_t								_client_max_body_size;
		std::string							_path_error_page;

	public:

		Server(void);
		Server(std::string root, int port = 8080);
		Server(Server const & src);
		virtual ~Server(void);
		Server &							operator=(Server const &rhs);

		Server &							add_port(int port);
		void								start(int worker);

		port_vector &						get_server_socket();
		ServerSocket const &				get_server_socket(int port) const;
		const bool	&						get_auto_index() const;

		Server &							set_name(std::string name);
		Server &							set_root(std::string root);
		Server &							set_auto_index(bool auto_index);
		Server &							set_client_max_body_size(size_t limit);
		Server &							set_path_error_page(std::string path);
		void								print() const;

};

#endif
