/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:23:05 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/30 17:03:33 by mchardin         ###   ########.fr       */
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
		_CGI_map = rhs._CGI_map;
		_return_list = rhs._return_list;
	}
	return *this;
}

Server &
Server::add_port(int const port)
{
	_server_sockets.insert(std::pair<int, ServerSocket>(port, ServerSocket(port)));
	return(*this);
}

Server &
Server::add_listen(int const port, std::string const ip, bool active)
{
	std::pair<port_map::iterator, bool>	pair;
	port_map::iterator					it;

	pair = _server_sockets.insert(std::pair<int, ServerSocket>(port, ServerSocket(port, ip)));
	it = pair.first;
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
	// std::cerr << "INDEX LIST SIZE : " << _index.size() << std::endl; //W
	return(*this);
}

Server &
Server::add_method(AMethod *method)
{
	if (!get_method(method->get_name())) //else error?
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
	for (port_map::iterator it = _server_sockets.begin(); it != _server_sockets.end() ; it++)
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

Server::port_map &
Server::get_map_socket(void)
{
	return (_server_sockets);
}

const Server::port_map &
Server::get_map_socket(void) const
{
	return (_server_sockets);
}

ServerSocket &
Server::get_server_socket(int port)
{
	return _server_sockets.at(port);
}

ServerSocket const &
Server::get_server_socket(int port) const
{
	return _server_sockets.at(port);
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
Server::get_method(const std::string &name) // TO TEST
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
			ss << "<a href=\"" << request.get_path();
			// std::cout << "last : " << request.get_path()[request.get_path().length() - 1] << std::endl;
			if (request.get_path()[request.get_path().length() - 1] != '/')
				ss << "\\";
			ss << entry->d_name << "\">" << entry->d_name << "</a>\n";
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

bool
Server::has_port(int port)
{
	if (_server_sockets.find(port) == _server_sockets.end())
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
	_path_error_page = path;
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
	port_map::iterator it	= _server_sockets.begin();
	port_map::iterator ite	= _server_sockets.end();

	for (; it != ite; it++)
	{
		if (it->second.get_socket() == socket)
			return (&(it->second));
	}
	return (0);
}

void
Server::print() const
{
	std::cout << "Server " << _name << std::endl;
	for (port_map::const_iterator it = _server_sockets.begin(); it != _server_sockets.end(); it++)
	{
		it->second.print();
	}
	for (cgi_map::const_iterator it = _CGI_map.begin(); it != _CGI_map.end(); it++)
	{
		std::cerr << "CGI : " << it->first << std::endl;
		
		it->second.print();
	}
	if (_server_sockets.size() == 0)
		std::cout << "no port found" << std::endl;
	std::cout << "Auto Index : " << (_auto_index ? "on":"off") << std::endl;
	if (_index.size())
	{
		std::cout << "Index list : ";
		for (std::list<std::string>::const_iterator it2 = _index.begin(); it2 != _index.end(); it2++)
		{
			std::cout << "  \"" << *it2 << "\" ";
		}
		std::cout << std::endl;
	}
	if (_methods.size())
	{
		std::cout << "Authorised Methods : ";
		for (std::list<AMethod*>::const_iterator it3 = _methods.begin(); it3 != _methods.end(); it3++)
		{
			std::cout << "\"" << (*it3)->get_name() << "\" ";
		}
		std::cout << std::endl;
	}
	if (_return_list.size())
	{
		std::cout << "Returns : " << std::endl;
		for (return_list::const_iterator it4 = _return_list.begin(); it4 != _return_list.end(); it4++)
		{
			std::cout << " - " << it4->get_code() << " : \"" << it4->get_ressource() << "\"" << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "client_max_body_size : " << _client_max_body_size << std::endl;
	std::cout << std::endl;
}
