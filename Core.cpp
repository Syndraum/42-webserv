/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roalvare <roalvare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 18:13:51 by syndraum          #+#    #+#             */
/*   Updated: 2021/07/20 12:09:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"

Core::Core(void) :
_worker(3)
//_maxfd(-1),
{
	_SIZE_SOCK_ADDR = sizeof(struct sockaddr_in);
	_methods
		.add_method(new MethodGet())
		.add_method(new MethodDelete())
		;
	_br.set_library(&_methods);
}

Core::Core(Core const & src)
{
	*this = src;
}

Core::~Core() {}

Core &
Core::operator=(Core const & rhs)
{
	if (&rhs != this)
		this->_worker = rhs._worker;
	return *this;
}

void
Core::start()
{
	HandlerRequest		hr(_br);
	std::vector<int>	active_socket;
	try{

		for (size_t i = 0; i < _servers.size(); i++)
		{
			_servers[i].start(_worker);
		}
	}
	catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "test" << std::endl;

		return ;
	}
print();
	_pfdh.init(_servers);
	while (true)
	{
//		poll(&(_pfdh.get_pfd().front()), _pfdh.get_pfd().size(), 60000);
		_pfdh.watch();
		_pfdh.accept_connection(_servers, _client);
//		_accept_connection();

		client_vector::iterator client = hr.handle(_client);
		if (client != _client.end())
			remove_client(client);
	}
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

int	
Core::get_worker(void) const
{
	return (_worker);
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

void
Core::print() const
{
	for (size_t i = 0; i < _servers.size(); i++)
	{
		_servers[i].print();
	}
	if (_servers.size() == 0)
		std::cout << "no Server found \n";
}

void
Core::remove_client(client_vector::iterator it)
{
	_pfdh.erase();
	close(it->get_socket());
	_client.erase(it);
}
