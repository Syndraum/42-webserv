#ifndef HANDLERREQUEST
# define HANDLERREQUEST

# include "Request.hpp"
# include "Server.hpp"
# include "BuilderRequest.hpp"
# include "ClientSocket.hpp"
# include "HandlerResponse.hpp"
# include "StrategyAccept.hpp"
# include "StrategyError.hpp"
# include "StrategyIndex.hpp"
# include "StrategyCGI.hpp"

class HandlerRequest
{
	Request *			_request;
	Server *			_server;
	ClientSocket *		_client;
	BuilderRequest &	_builder;
	HandlerResponse		_handler_response;

	HandlerRequest(void);
public:

	HandlerRequest(BuilderRequest &);
	HandlerRequest(HandlerRequest const & src);
	virtual ~HandlerRequest(void);
	HandlerRequest &	operator=(HandlerRequest const &rhs);

	HandlerRequest &	set_request(Request *);
	HandlerRequest &	set_server(Server *);
	HandlerRequest &	set_client(ClientSocket *);
	void	handle(std::vector<ClientSocket> &);
	void	parse();
	void	set_path();
	bool	is_complete() const;

};

#endif
