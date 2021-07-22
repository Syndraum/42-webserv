#ifndef CLIENT
# define CLIENT

# include "ClientSocket.hpp"
# include "Server.hpp"
# include "Request.hpp"

class Client
{
	Request			_request;
	Server &		_server;
	ClientSocket &	_socket;

	Client(void);
public:

	Client(Server &, ClientSocket &);
	Client(Client const & src);
	virtual ~Client(void);
	Client &	operator=(Client const &rhs);

	Request &	get_request();
	Server &	get_server();
private:

};

#endif
