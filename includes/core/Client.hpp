#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ClientSocket.hpp"
# include "Server.hpp"
# include "Request.hpp"

class Client
{
	Request			_request;
	ClientSocket	_socket;
	Server *		_server;
	ServerSocket *	_server_socket;

	Client(void);
public:

	Client(Server &, ServerSocket &);
	Client(Client const & src);
	virtual ~Client(void);
	Client &	operator=(Client const &rhs);
	bool operator==(const Client & rhs) const
	{
		if (this->_socket.get_socket() == rhs._socket.get_socket())
			return (true);
		return (false);
	}

	Request &		get_request();
	Request const &	get_request() const;
	ClientSocket &	get_socket_struct();
	int				get_socket();
	Server &		get_server();
	Server const &	get_server() const;
	ServerSocket &	get_server_socket();
	std::string		get_full_path() const;
	void			set_server(Server *);
	void			set_server_socket(ServerSocket *);

private:

};

#endif
