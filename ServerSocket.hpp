#ifndef SERVERSOCKET
# define SERVERSOCKET

# include <sys/socket.h>
# include <netinet/in.h>

# include <iostream>
# include <cerrno>
# include <cstring>

class ServerSocket
{
public:
	ServerSocket(int port = 80);
	ServerSocket(ServerSocket const & src);
	virtual ~ServerSocket(void);
	ServerSocket &	operator=(ServerSocket const &rhs);

	void			setupSocket();
	void			bindSocket();
	void			listenSocket(int worker_connection);

	ServerSocket *	setPort(int port);
	int				getPort();
	int				getSocket();
	sockaddr_in		& getServer();

	void			print();

private:
	int			_port;
	int			_socket;
	sockaddr_in _address;
};

#endif
