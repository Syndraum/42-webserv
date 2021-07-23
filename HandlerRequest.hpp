#ifndef HANDLERREQUEST
# define HANDLERREQUEST

# include "Request.hpp"
# include "Server.hpp"
# include "BuilderRequest.hpp"
# include "Client.hpp"
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
	typedef std::vector<Client>		clients;
	typedef clients::iterator		clients_iterator;

	HandlerRequest(BuilderRequest &);
	HandlerRequest(HandlerRequest const & src);
	virtual ~HandlerRequest(void);
	HandlerRequest &	operator=(HandlerRequest const &rhs);

	HandlerRequest &	set_request(Request *);
	HandlerRequest &	set_server(Server *);
	HandlerRequest &	set_client(ClientSocket *);
	clients_iterator	handle(clients &);
	void				parse();
	void				set_path();
	bool				is_complete() const;

};

#endif
