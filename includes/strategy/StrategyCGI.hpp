#ifndef STRATEGY_CGI_HPP
# define STRATEGY_CGI_HPP

# include "IResponseStrategy.hpp"
# include "RequestCGI.hpp"
# include "CGI.hpp"
# include "Info.hpp"
# include "ReaderFileDescriptor.hpp"
# include "HandlerResponseCGI.hpp"
# include "Pipe.hpp"

class StrategyCGI : public IResponseStrategy
{
public:
	enum cgi_state {
		INIT,
		WRITE_BODY,
		PARSE_HEADER,
		PREPARE_REPONSE,
		END
	};
private:
	CGI &				_cgi;
	RequestCGI			_request;
	HandlerResponseCGI	_handler;
	Pipe				_pipe;
	cgi_state			_state;
	Message *			_response_cgi;

	StrategyCGI(void);

public:
	StrategyCGI(CGI &);
	StrategyCGI(StrategyCGI const & src);
	virtual ~StrategyCGI(void);
	StrategyCGI &	operator=(StrategyCGI const &rhs);
	virtual IResponseStrategy *	clone() const;

private:
	virtual Response *	create(Client &);
	void				_prepare(Client &);
	void				handle_status(const Message &, Response &, Server & server);
	cgi_state			get_state() const;
	void				clear();
	void				init(Client &);
	void				write_body(Client &);
	void				parse_header();
	void				prepare_response(Client &);

};

#endif
