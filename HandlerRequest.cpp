#include "HandlerRequest.hpp"

HandlerRequest::HandlerRequest(
	Request &				request,
	Server &				server,
	BuilderRequest &	builder,
	ClientSocket & client) :
		_request(request),
		_server(server),
		_builder(builder),
		_socket(client)
{}

HandlerRequest::HandlerRequest(HandlerRequest const & src) :
	_request(src._request),
	_server(src._server),
	_builder(src._builder),
	_socket(src._socket)
{}

HandlerRequest::~HandlerRequest(void)
{
	
}

HandlerRequest &
HandlerRequest::operator=(HandlerRequest const & rhs)
{
	if (this != &rhs){
		_request = rhs._request;
		_server = rhs._server;
	}
	return *this;
}

void
HandlerRequest::set_request(const Request & request)
{
	_request = request;
}

void
HandlerRequest::set_server(const Server & server)
{
	_server = server;
}

void 
HandlerRequest::parse()
{
	std::string		line;
	int				gnl_ret = 1;
	
	_builder.set_request(&_request);
	while (gnl_ret && (gnl_ret = _socket.get_next_line(line)))
	{
		if (gnl_ret == -1)
			return ;
		std::cout << "line: " << line << std::endl;
		line += "\r";
		_builder.parse_request(line);
		if (_request.get_header_lock())
		{
			_socket.reset_buffer();
			gnl_ret = 0;
		}
	}
}

void
HandlerRequest::set_path()
{
	// std::string relative_path;
	_request.set_path(_request.get_path() + _server.get_index(_request.get_path()));
}

bool
HandlerRequest::is_complete() const
{
	return (_request.get_header_lock() && _request.get_body_lock());
}