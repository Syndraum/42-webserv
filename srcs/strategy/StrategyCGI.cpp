/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StrategyCGI.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:33:13 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 20:30:16 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StrategyCGI.hpp"

StrategyCGI::StrategyCGI(CGI & cgi) :
IResponseStrategy(),
_cgi(cgi),
_request(cgi),
_handler(1),
_state(INIT),
_response_cgi(0)
{}

StrategyCGI::StrategyCGI(StrategyCGI const & src) :
IResponseStrategy(),
_cgi(src._cgi), 
_request(src._request),
_handler(src._handler)
{
	*this = src;
}

StrategyCGI::~StrategyCGI(void)
{
	clear();
}

StrategyCGI &	StrategyCGI::operator=(StrategyCGI const & rhs)
{
	IResponseStrategy::operator=(rhs);
	if (this != &rhs)
	{
		_cgi = rhs._cgi;
		_request =  rhs._request;
		_handler = rhs._handler;
		_pipe = rhs._pipe;
		_state = rhs._state;
		_response_cgi = rhs._response_cgi;
	}
	return *this;
}

IResponseStrategy *	
StrategyCGI::clone() const
{
	StrategyCGI * copy = new StrategyCGI(_cgi);
	*copy = *this;
	return (copy);
}

Response *
StrategyCGI::create(Client & client)
{
	Response *				response		= client.get_response();

	if (response == 0)
		response = new Response();
	try
	{
		switch (_state)
		{
		case StrategyCGI::INIT:
			init(client);
			break ;
		case StrategyCGI::WRITE_BODY:
			write_body(client);
			break ;
		case StrategyCGI::PARSE_HEADER:
			parse_header();
			break ;
		case StrategyCGI::PREPARE_REPONSE:
			prepare_response(client);
			break ;
		case StrategyCGI::END:
			_finish = true;
			break ;
		default :
			break ;
		}
	}
	catch (std::exception& e)
	{
		response->set_error(500, client.get_server().get_path_error_page());
		_state = END;
		_finish = true;
	}
	return (response);
}

void
StrategyCGI::handle_status(const Message & message, Response & response, Server & server)
{
	std::string	status = message.get_header("Status");
	size_t		pos;

	if ((pos = status.find(" ", 0)) != std::string::npos)
	{
		try
		{
			response.set_code(std::atoi(status.substr(0, pos).c_str()));
			if (response.get_code() >= 400){
				response.set_error(response.get_code(), server.get_path_error_page());
			}
		}
		catch (std::exception& e)
		{
			response.set_error(500, server.get_path_error_page());
		}
	}
	else
	{
		response.set_error(500, server.get_path_error_page());
	}
	
}

void
StrategyCGI::_prepare(Client & client)
{
	Request &		request_http	= client.get_request();
	Server &		server			= client.get_server();
	ServerSocket &	server_socket	= client.get_server_socket();

	if (!request_http.has_header("Content-Length")){
		_request.add_header("CONTENT_LENGTH", 0);
	}
	else {
		_request.add_header("CONTENT_LENGTH", request_http.get_header("Content-Length"));
		if (request_http.has_header("Content-Type"))
			_request.add_header("CONTENT_TYPE", request_http.get_header("Content-Type"));
	}
	_request
		.add_header("AUTH_TYPE", "")
		.add_header("GATEWAY_INTERFACE", Info::cgi_revision)
		.add_header("SCRIPT_FILENAME", server.get_full_path(request_http.get_uri().get_path()))
		.add_header("PATH_INFO", server.get_full_path(request_http.get_uri().get_path()))
		.add_header("QUERY_STRING", request_http.get_uri().get_query_string())
		.add_header("REMOTE_ADDR", client.get_socket_struct().get_ip())
		.add_header("REQUEST_METHOD", request_http.get_method()->get_name())
		.add_header("SCRIPT_NAME", request_http.get_uri().get_path())
		.add_header("SERVER_NAME", server_socket.get_ip())
		.add_header("SERVER_PORT", server_socket.get_port())
		.add_header("SERVER_PROTOCOL", Info::http_revision)
		.add_header("SERVER_SOFTWARE", Info::server_name + "/" + Info::version)
	;
	if (_request.get_header("PATH_INFO") != "")
		_request.add_header("PATH_TRANSLATED", server.get_full_path(request_http.get_uri().get_extra_path()));
}

StrategyCGI::cgi_state
StrategyCGI::get_state() const
{
	return (_state);
}

void
StrategyCGI::clear()
{
	delete (_response_cgi);
	_response_cgi = 0;
}

void
StrategyCGI::init(Client & client)
{
	this->_prepare(client);
	_request.set_body(client.get_request().get_body());
	_cgi.start(_request, client.get_full_path(), _pipe);
	_state = WRITE_BODY;
}

void
StrategyCGI::write_body(Client & client)
{
	AReaderFileDescriptor &	reader	= client.get_socket_struct().get_reader();
	int n_write = 0;

	n_write = reader.write_body(_pipe.get_in()[1]);
	if (n_write == 0)
		_state = PARSE_HEADER;
}

void
StrategyCGI::parse_header()
{
	if (_handler.get_response() == 0)
	{
		_handler.set_fd(_pipe.get_out()[0]);
		_handler.init();
	}
	try
	{
		_handler.parse();
	}
	catch (const AReaderFileDescriptor::EndOfFile& e)
	{
		_state = PREPARE_REPONSE;
	}
	if (_handler.get_response()->get_body_lock())
		_state = PREPARE_REPONSE;
}

void
StrategyCGI::prepare_response(Client & client)
{
	Response *	response	= client.get_response();

	close(_pipe.get_out()[0]);
	close(_pipe.get_err()[0]);
	close(_pipe.get_in()[1]);
	_response_cgi = _handler.get_response();

	response->set_code(200);
	response->add_header("Content-Type", _response_cgi->get_header("Content-Type"));
	response->set_body(_response_cgi->get_body());
	if (_response_cgi->has_header("Status"))
		handle_status(*_response_cgi, *response, client.get_server());
	if (!_response_cgi->has_header("Content-Type") || _response_cgi->get_header("Content-Type") == "")
		response->set_error(500, client.get_server().get_path_error_page());
	clear();
	_state = END;
}
