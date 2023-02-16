/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:51 by syndraum          #+#    #+#             */
/*   Updated: 2021/11/19 20:52:31 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"

Core::Core(void) :
_worker(1024)
{
	_SIZE_SOCK_ADDR = sizeof(struct sockaddr_in);
	_methods
		.add_method(new MethodGet())
		.add_method(new MethodDelete())
		.add_method(new MethodPost())
		;
	_br.set_library(&_methods);
}

Core::Core(Core const & src)
{
	*this = src;
}

Core::~Core()
{
	clean();
}

Core &
Core::operator=(Core const & rhs)
{
	if (&rhs != this)
		this->_worker = rhs._worker;
	return *this;
}

int
Core::init(int argc, char * argv[], char *env[])
{
	std::string path_config_file = Info::path_config_file;

	if (argc > 2)
	{
		std::cerr << "Error: too many arguments" << std::endl;
		return (2);
	}
	if (argc == 2)
		path_config_file = argv[1];
	
	Reader reader(path_config_file);
	try
	{
		reader.open();
	}
	catch (std::exception& e)
	{
		std::cerr << "Error: Configuration file: " << path_config_file << " not found" << std::endl;
		return (1);
	}
	try
	{
		BuilderCore builder_core(this);
		builder_core.build(reader.get_ifs());
		builder_core.parse_mime_type();
	}
	catch (std::exception& e)
	{
		return (3);
	}
	Info::env = env;
	return (0);
}

void
Core::start()
{
	bool				run	= true;
	HandlerRequest		hr(_br);
	std::vector<int>	active_socket;

	try
	{
		for (size_t i = 0; i < _servers.size(); i++)
			_servers[i].start(_worker);
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: " << e.what() << '\n';
		return ;
	}
	_pfdh.init(_servers);
	_pfdh.set_hr(hr);
	while (run)
	{
		try
		{
			_pfdh.watch();
			_pfdh.handle(_servers, _client);
			// if (hr.get_account() >= 1000)
			// 	run = false;
		}
		catch(const HandlerPollFD::ErrorPoll& e)
		{
			run = false;
		}
	}
}

void
Core::clean()
{
	Extension::delete_instance();
	
	for (size_t i = 0; i < _client.size(); i++)
		_client[i].get_socket_struct().sclose();
	_client.clear();
	_servers.clear();
}

void
Core::add_server(Server & server)
{
	_servers.push_back(server);
}

Server &
Core::add_server()
{
	_servers.push_back(Server());
	return(_servers.back());
}

Server	const &
Core::get_server(int index) const
{
	return (_servers.at(index));
}

size_t
Core::get_server_count() const
{
	return (_servers.size());
}

int	
Core::get_worker(void) const
{
	return (_worker);
}

const MethodLibrary &
Core::get_library(void) const
{
	return (_methods);
}

Core &
Core::set_worker(int worker)
{
	_worker = worker;
	return(*this);
}

void
Core::set_extension(Extension * extension)
{
	_extension = extension;
}

bool
Core::has_host_port(const std::string & ip, int port) const
{
	for (size_t i = 0; i < _servers.size(); i++)
	{
		const Server & server = _servers[i];

		for (Server::port_vector::const_iterator it = server.get_vector_socket().begin();
			it != server.get_vector_socket().end(); it++)
		{
			const ServerSocket & server_socket = it->second;

			if (server_socket.get_port() == port && ip == server_socket.get_ip())
				return true;
		}
	}
	return false;
}

AMethod *
Core::get_method(std::string const & name) const
{
	return (_methods.clone_method(name));
}
