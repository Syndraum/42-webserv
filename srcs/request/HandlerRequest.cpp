#include "HandlerRequest.hpp"

HandlerRequest::HandlerRequest(
	BuilderRequest &	builder
	) :
		_client(0),
		_builder(builder)
{}

HandlerRequest::HandlerRequest(HandlerRequest const & src) :
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
		_client = rhs._client;
	}
	return *this;
}

HandlerRequest &
HandlerRequest::set_client(Client * client)
{
	_client = client;
	return *this;
}

Request &
HandlerRequest::get_request()
{
	return (_client->get_request());
}

const Request &
HandlerRequest::get_request() const
{
	return (_client->get_request());
}

Server &
HandlerRequest::get_server()
{
	return (_client->get_server());
}

ClientSocket &
HandlerRequest::get_client_socket()
{
	return (_client->get_socket_struct());
}

HandlerRequest::clients_iterator
HandlerRequest::handle(clients & vector)
{
	for (clients_iterator it = vector.begin(); it != vector.end(); it++)
	{
		set_client(&(*it));
		try{
			parse();
			if (!is_complete())
				continue;
			get_request().set_path(get_request().get_path() + get_server().get_index(get_request().get_path()));
			if (get_server().get_cgi_map().find("." + Extension::get_extension(get_request().get_path())) != get_server().get_cgi_map().end())
			{
				_handler_response.set_strategy(new StrategyCGI(get_server().get_cgi_map()["." + Extension::get_extension(get_request().get_path())]));
			}
			else
			{
				if (get_server().is_directory(get_request()))
				{
					if (!get_server().get_auto_index())
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
		_handler_response.do_strategy(*_client);
		_handler_response.send(it->get_socket());
		get_request().reset();
		return (it);
	}
	return (vector.end());
}

void 
HandlerRequest::parse()
{
	std::string		line;
	int				gnl_ret = 1;
	
	_builder.set_message(&get_request());
	while (gnl_ret && (gnl_ret = get_client_socket().get_reader().get_next_line(line)))
	{
		if (gnl_ret == -1)
			return ;
		std::cout << "line: " << line << std::endl;
		line += "\r";
		_builder.parse_request(line);
		if (get_request().get_header_lock())
		{
			if (get_request().get_header("Content-Length") == "")
			{
				std::cout << "No Content-Length" << std::endl;
				get_client_socket().get_reader().read_until_end(line);
				//std::cout << "_buffer: " << _buffer << std::endl;
			}
			else
			{
				std::cout << "Content-Length : " << get_request().get_header("Content-Length") << std::endl;

				get_client_socket().get_reader().read_body(line, std::atoi(get_request().get_header("Content-Length").c_str()));
			}
			get_request().set_body_lock(true);
			get_client_socket().get_reader()._reset_buffer();
			gnl_ret = 0;
		}
	}
}

void
HandlerRequest::set_path()
{
	// std::string relative_path;
	get_request().set_path(get_request().get_path() + get_server().get_index(get_request().get_path()));
}

bool
HandlerRequest::is_complete() const
{
	return (get_request().get_header_lock() && get_request().get_body_lock());
}
