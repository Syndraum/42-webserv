#include "HandlerRequest.hpp"

HandlerRequest::HandlerRequest(
	BuilderRequest &	builder
	) :
		_request(0),
		_server(0),
		_client(0),
		_builder(builder)
{}

HandlerRequest::HandlerRequest(HandlerRequest const & src) :
	_request(src._request),
	_server(src._server),
	_client(src._client),
	_builder(src._builder)
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

HandlerRequest &
HandlerRequest::set_request(Request * request)
{
	_request = request;
	return *this;
}

HandlerRequest &
HandlerRequest::set_server(Server * server)
{
	_server = server;
	return *this;
}

HandlerRequest &
HandlerRequest::set_client(ClientSocket * client)
{
	_client = client;
	return *this;
}

void
HandlerRequest::handle(std::vector<Client> & map)
{
	for (std::vector<Client>::iterator it = map.begin(); it != map.end(); it++)
	{
		set_client(&it->get_socket_stuct())
		.set_request(&it->get_request())
		.set_server(&it->get_server())
		;
		try{
			parse();
			if (!is_complete())
				continue;
			_request->set_path(_request->get_path() + _server->get_index(_request->get_path()));
			if (_server->get_cgi_map().find("." + Extension::get_extension(_request->get_path())) != _server->get_cgi_map().end())
			{
				_handler_response.set_strategy(new StrategyCGI(_server->get_cgi_map()["." + Extension::get_extension(_request->get_path())]));
			}
			else
			{
				if (_server->is_directory(*_request))
				{
					if (!_server->get_auto_index())
						_handler_response.set_strategy(new StrategyError(403));
					else
						_handler_response.set_strategy(new StrategyIndex());
				}
				else
					_handler_response.set_strategy(new StrategyAccept());
			}
			
		}
		catch (BuilderRequest::BadRequest &e)
		{
			_handler_response.set_strategy(new StrategyError(400));
		}
		catch (BuilderRequest::BadHttpVersion &e)
		{
			_handler_response.set_strategy(new StrategyError(505));
		}
		catch (BuilderRequest::MethodNotImplemented &e)
		{
			_handler_response.set_strategy(new StrategyError(501));
		}
		_handler_response.do_strategy(*_server, *_request);
		_handler_response.send(it->get_socket());
		_request->reset();
		close( it->get_socket() );  
		map.erase(it);  
		break;
	}
}

void 
HandlerRequest::parse()
{
	std::string		line;
	int				gnl_ret = 1;
	
	_builder.set_request(_request);
	while (gnl_ret && (gnl_ret = _client->get_next_line(line)))
	{
		if (gnl_ret == -1)
			return ;
		std::cout << "line: " << line << std::endl;
		line += "\r";
		_builder.parse_request(line);
		if (_request->get_header_lock())
		{
			_client->reset_buffer();
			gnl_ret = 0;
		}
	}
}

void
HandlerRequest::set_path()
{
	// std::string relative_path;
	_request->set_path(_request->get_path() + _server->get_index(_request->get_path()));
}

bool
HandlerRequest::is_complete() const
{
	return (_request->get_header_lock() && _request->get_body_lock());
}