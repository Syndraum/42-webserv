#ifndef SERVERSOCKET
# define SERVERSOCKET

# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>

class ServerSocket
{
public:
	ServerSocket(int port = 80);
	ServerSocket(ServerSocket const & src);
	virtual ~ServerSocket(void);
	ServerSocket &	operator=(ServerSocket const &rhs);

	void			SetupSocket();
	void			bindSocket();
	void			listenSocket(int worker_connection);

	ServerSocket *	SetPort(int port);
	int				GetPort();
	int				GetSocket();
	sockaddr_in		& GetServer();

private:
	int	_port;
	int	_socket;
	sockaddr_in _server;
};

#endif
