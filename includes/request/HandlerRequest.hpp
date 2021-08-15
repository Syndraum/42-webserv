#ifndef HANDLER_REQUEST_HPP
# define HANDLER_REQUEST_HPP

# include <exception>
# include "Request.hpp"
# include "Server.hpp"
# include "BuilderRequest.hpp"
# include "Client.hpp"
# include "HandlerResponse.hpp"
# include "StrategyAccept.hpp"
# include "StrategyError.hpp"
# include "StrategyIndex.hpp"
# include "StrategyCGI.hpp"
# include "StrategyReturn.hpp"

class HandlerRequest
{
	Client *			_client;
	BuilderRequest &	_builder;
	HandlerResponse		_handler_response;

	HandlerRequest(void);
public:
	typedef std::vector<Client>		clients;
	typedef std::vector<Server>		servers;
	typedef clients::iterator		clients_iterator;

	HandlerRequest(BuilderRequest &);
	HandlerRequest(HandlerRequest const & src);
	virtual ~HandlerRequest(void);
	HandlerRequest &	operator=(HandlerRequest const &rhs);

	HandlerRequest &	set_client(Client *);
	Request &			get_request();
	const Request &		get_request() const;
	Server &			get_server();
	ClientSocket &		get_client_socket();

	clients_iterator	handle(clients &, servers &);
	void				parse();
	void				set_index();
	bool				is_complete() const;
	void				check_host(servers &);
	void				check_body_size(Client const &) const;
	void				check_method_exist(Client const &) const;

	class BodyTooLong : public std::exception
	{
		virtual const char*	what() const throw(){
			return "Body toot long";
		}
	};
	class MethodNotAllowed : public std::exception
	{
		virtual const char*	what() const throw(){
			return "Method not allowed";
		}
	};
};

#endif
