/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:22:23 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/30 16:46:46 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

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
# include <sys/types.h>
# include <dirent.h>
# include <set>
# include <sstream>
# include "Request.hpp"
# include "AMethod.hpp"
# include "Redirection.hpp"

class CGI;
class AMethod;

class Server
{
	public:

		typedef std::map<int, ServerSocket>	port_map;
		typedef std::list<Redirection>	return_list;
		typedef std::map<std::string, CGI>	cgi_map;
		typedef std::pair<std::string, CGI>	cgi_pair;

	private:

		std::string							_name;
		port_map							_server_sockets;
		std::string							_root;
		std::list<std::string>				_index;
		std::list<AMethod *>				_methods;
		bool								_auto_index;
		size_t								_client_max_body_size;
		std::string							_path_error_page;
		cgi_map								_CGI_map;
		return_list							_return_list;

	public:

		Server(void);
		Server(std::string const &root, int const port = 8080);
		Server(Server const & src);
		virtual ~Server(void);
		Server &							operator=(Server const &rhs);

		Server &							add_port(int const port);
		Server &							add_return(int const code, std::string const uri);
		Server &							add_listen(int const port, std::string const address, bool = true);
		Server &							add_index(std::string const & index);
		Server &							add_method(AMethod *method);
		Server &							add_CGI(std::string name, CGI content);
		void								start(int const worker);

		const std::string &					get_name() const;
		port_map &							get_map_socket();
		const port_map &					get_map_socket() const;
		ServerSocket &						get_server_socket(int port);
		const ServerSocket &				get_server_socket(int port) const;
		const bool	&						get_auto_index() const;
		size_t								get_client_max_body_size() const;
		const std::string &					get_path_error_page() const;
		const std::string &					get_root() const;
		std::string 						get_index(const std::string &);
		AMethod *	 						get_method(const std::string &);
		std::string							get_full_path(const std::string & uri);
		std::string							get_index_page(const Request & uri);
		CGI &								get_cgi(const std::string &);
		bool								has_cgi(const std::string &);
		bool								has_port(int port);

		std::list<std::string> &			get_list_index();
		std::list<AMethod *> &				get_list_method();
		const std::list<AMethod *> &		get_list_method() const;
		const return_list &					get_return_list() const;

		Server &							set_name(std::string const & name);
		Server &							set_root(std::string const & root);
		Server &							set_auto_index(bool const auto_index);
		Server &							set_client_max_body_size(size_t const limit);
		Server &							set_path_error_page(std::string const & path);
		bool								is_directory(const Request &);
		void								print() const;

};

#endif
