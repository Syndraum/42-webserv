#ifndef HANDLERREQUEST
# define HANDLERREQUEST

# include "Request.hpp"
# include "Server.hpp"
# include "BuilderRequest.hpp"
# include "ClientSocket.hpp"

class HandlerRequest
{
	Request &			_request;
	Server &			_server;
	BuilderRequest &	_builder;
	ClientSocket &		_socket;

	HandlerRequest(void);
public:

	HandlerRequest(Request &, Server &, BuilderRequest &, ClientSocket &);
	HandlerRequest(HandlerRequest const & src);
	virtual ~HandlerRequest(void);
	HandlerRequest &	operator=(HandlerRequest const &rhs);

	void	set_request(const Request &);
	void	set_server(const Server &);
	void	parse();
	void	set_path();
	bool	is_complete() const;

};

#endif
