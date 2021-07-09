/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 14:23:05 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/09 12:29:42 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void) :
_name("_"),
_auto_index(false),
_client_max_body_size(5)
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
		_auto_index = rhs._auto_index;
		_client_max_body_size = rhs._client_max_body_size;
		_path_error_page = rhs._path_error_page;
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
Server::add_index(std::string const &index)
{
	_index.push_back(index);
	std::cerr << "INDEX LIST SIZE : " << _index.size() << std::endl;
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

		ss.setup_socket();
		ss.bind_socket();
		ss.listen_socket(worker);
	}
}

Server::port_map &
Server::get_server_socket(void)
{
	return (_server_sockets);
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
	for (std::list<std::string>::iterator it = _index.begin(); it != _index.end(); it++)
	{
		if (files.find(*it) != files.end())
			return (*it);
	}
	return ("");
}

std::string
Server::get_full_path(const std::string & uri)
{
	return (std::string (_root + uri));
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
	std::cout << "Auto Index : "<< _auto_index << std::endl;
	std::cout << "INDEX LIST SIZE : " << _index.size() << std::endl;
	for (std::list<std::string>::const_iterator it2 = _index.begin(); it2 != _index.end(); it2++)
	{
		std::cout << "\"" << *it2 << "\"" << std::endl;
	}
}
