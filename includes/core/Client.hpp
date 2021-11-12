#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ClientSocket.hpp"
# include "Server.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "IResponseStrategy.hpp"

class IResponseStrategy;

class Client
{
public:
	enum request_state {
		READ_HEADER,
		STRATEGY,
		SEND_RESPONSE,
		END
	};
private:
	Request					_request;
	ClientSocket			_socket;
	Server *				_server;
	ServerSocket *			_server_socket;
	IResponseStrategy *		_strategy;
	Response *				_response;
	request_state			_state;

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
	Response *		get_response();
	std::string		get_full_path() const;
	request_state	get_state() const;
	void			set_server(Server *);
	void			set_server_socket(ServerSocket *);

	void	set_strategy(IResponseStrategy *);
	void	do_strategy(Client &);
	void	send(int fd);
	void	clean_reponse();

private:

};

#endif
