#ifndef CORE
# define CORE

#include "Server.hpp"
#include <vector>

class Core
{
public:

	Core(void);
	Core(Core const & src);
	virtual ~Core(void);
	Core &	operator=(Core const &rhs);

	void	start();
	void	addServer(Server & server);
	void	addServer();
	Server	&	getServer(int index = 0);

	void	print();

private:
	std::vector<Server>	_servers;
	int					_worker;
	fd_set				_readfds;
	int					_maxfd;
	int					_nbActive;
	std::vector<int>	_clientSockets;
};

#endif
