/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:23:05 by syndraum          #+#    #+#             */
/*   Updated: 2021/11/19 23:02:52 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void) :
_name("_"),
_server_sockets(),
_root("html"),
_index(),
_methods(),
_auto_index(false),
_client_max_body_size(5 << 20),
_path_error_page("./config/error.html"),
_upload_path("."),
_CGI_map(),
_return_list()
{}

Server::Server(Server const & src)
{
	*this = src;
}

Server::~Server(void) {}

Server &
Server::operator=(Server const & rhs)
{
	if (&rhs != this){
		_name = rhs._name;
		_root = rhs._root;
		_server_sockets = rhs._server_sockets;
		_index = rhs._index;
		_methods = rhs._methods;
		_auto_index = rhs._auto_index;
		_client_max_body_size = rhs._client_max_body_size;
		_path_error_page = rhs._path_error_page;
		_upload_path = rhs._upload_path;
		_CGI_map = rhs._CGI_map;
		_return_list = rhs._return_list;
	}
	return *this;
}

Server &
Server::add_listen(int const port, std::string const ip, bool active)
{
	std::pair<port_vector::iterator, bool>	pair;
	port_vector::iterator					it;

	for (it = _server_sockets.begin(); it != _server_sockets.end(); it++)
		if (it->first == port && it->second.get_ip() == ip)
			throw Server::PortAlreadyUsed();
	it = _server_sockets.insert(_server_sockets.end(), std::pair<int, ServerSocket>(port, ServerSocket(port, ip)));
	it->second.set_active(active);
	return(*this);
}

Server &
Server::add_return(int const code, std::string const uri)
{
	_return_list.push_back(Redirection(code, uri));
	return(*this);
}

Server &
Server::add_index(std::string const &index)
{
	_index.push_back(index);
	return(*this);
}

Server &
Server::add_method(AMethod *method)
{
	if (!get_method(method->get_name()))
		_methods.push_back(method);
	return(*this);
}

Server &
Server::add_CGI(std::string name, CGI content)
{
	_CGI_map.insert(cgi_pair(name, content));
	return(*this);
}

void
Server::start(int const worker)
{
	for (port_vector::iterator it = _server_sockets.begin(); it != _server_sockets.end() ; it++)
	{
		ServerSocket & ss = it->second;

		if (ss.get_active())
		{
			ss.setup_socket();
			ss.bind_socket();
			ss.listen_socket(worker);
		}
	}
}

const std::string &
Server::get_name() const
{
	return (_name);
}

Server::port_vector &
Server::get_vector_socket(void)
{
	return (_server_sockets);
}

const Server::port_vector &
Server::get_vector_socket(void) const
{
	return (_server_sockets);
}

ServerSocket *
Server::get_server_socket(int port, std::string ip)
{
	port_vector::iterator					it;
	for (it = _server_sockets.begin(); it != _server_sockets.end(); it++)
	{
		if (it->first == port && it->second.get_ip() == ip)
		{
			return &it->second;
		}
	}
	return 0;
}

ServerSocket const *
Server::get_server_socket(int port, std::string ip) const
{
		port_vector::const_iterator					it;
	for (it = _server_sockets.begin(); it != _server_sockets.end(); it++)
	{
		if (it->first == port && it->second.get_ip() == ip)
		{
			return &it->second;
		}
	}
	return 0;
}

const bool &
Server::get_auto_index() const
{
	return (_auto_index);
}

size_t
Server::get_client_max_body_size() const
{
	return (_client_max_body_size);
}

const std::string &
Server::get_path_error_page() const
{
	return (_path_error_page);
}

const std::string &
Server::get_upload_path() const
{
	return (_upload_path);
}

const std::string &
Server::get_root() const
{
	return (_root);
}

std::string
Server::get_index(const std::string & uri)
{
	std::string					path;
	DIR *						directory;
	struct dirent *				entry;
	std::set<std::string>		files;

	path = get_full_path(uri);
	if ((directory = opendir(path.c_str())) != NULL)
	{
		while ((entry = readdir(directory)) != NULL)
			files.insert(entry->d_name);
	}
	else
		return ("");
	closedir(directory);
	for (std::list<std::string>::iterator it = _index.begin(); it != _index.end(); it++)
	{
		if (files.find(*it) != files.end())
			return (*it);
	}
	return ("");
}

AMethod *
Server::get_method(const std::string &name)
{
	for (std::list<AMethod *>::iterator it = _methods.begin(); it != _methods.end(); it++)
	{
		if (name == (*it)->get_name())
			return(*it);
	}
	return (0);
}

std::string
Server::get_full_path(const std::string & uri)
{
	return (std::string (_root + uri));
}

std::string
Server::get_index_page(const Request & request)
{
	std::stringstream ss;
	std::string					path;
	DIR *						directory;
	struct dirent *				entry;

	path = get_full_path(request.get_path());
	ss << "<html>\n<head><title>Index of " << request.get_path() << "</title></head>\n<body>\n<h1>Index of " << request.get_path() << "</h1><hr><pre>\n";
	if ((directory = opendir(path.c_str())) != NULL)
	{
		while ((entry = readdir(directory)) != NULL){
			if (entry->d_name[0] != '.' || (entry->d_name[0] == '.' && entry->d_name[1] == '.')){
				ss << "<a href=\"" << request.get_path();
				if (request.get_path()[request.get_path().length() - 1] != '/')
					ss << "\\";
				ss << entry->d_name << "\">" << entry->d_name << "</a>\n";
			}
		}
	}
	closedir (directory);
	ss << "</pre><hr></body>\n</html>";
	return (ss.str());
}

CGI &
Server::get_cgi(const std::string & key)
{
	return (_CGI_map.at("." + key));
}

bool
Server::has_cgi(const std::string & extension)
{
	if (_CGI_map.find("." + extension) == _CGI_map.end())
		return false;
	return true;
}

std::list<std::string> &
Server::get_list_index(void)
{
	return (_index);
}

std::list<AMethod *> &
Server::get_list_method(void)
{
	return (_methods);
}

const std::list<AMethod *> &
Server::get_list_method(void) const
{
	return (_methods);
}

const Server::return_list &
Server::get_return_list() const
{
	return (_return_list);
}

Server &
Server::set_name(std::string const & name)
{
	_name = name;
	return(*this);
}

Server &
Server::set_root(std::string const & root)
{
	_root = root;
	return(*this);
}

Server &
Server::set_auto_index(bool const auto_index)
{
	_auto_index = auto_index;
	return(*this);
}

Server &
Server::set_client_max_body_size(size_t const limit)
{
	_client_max_body_size = limit;
	return(*this);
}

Server &
Server::set_path_error_page(std::string const & path)
{
	if (!path.empty() && path[path.size() - 1] == '/')
		_path_error_page = path.substr(0, path.size() - 1);
	else
		_path_error_page = path;
	return(*this);
}

Server &
Server::set_upload_path(std::string const & path)
{
	if (!path.empty() && path[path.size() - 1] == '/')
		_upload_path = path.substr(0, path.size() - 1);
	else
		_upload_path = path;
	return(*this);
}

bool
Server::is_directory(const Request & request)
{
	std::string	path =		get_full_path(request.get_path());
	DIR *		directory;

	if ((directory = opendir(path.c_str())) == NULL)
		return (false);
	closedir(directory);
	return (true);
}

ServerSocket *
Server::find_socket(int socket)
{
	port_vector::iterator it	= _server_sockets.begin();
	port_vector::iterator ite	= _server_sockets.end();

	for (; it != ite; it++)
	{
		if (it->second.get_socket() == socket)
			return (&(it->second));
	}
	return (0);
}
