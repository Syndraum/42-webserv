#include "StrategyCGI.hpp"

StrategyCGI::StrategyCGI(CGI & cgi) :
IResponseStrategy(),
_cgi(cgi),
_request(cgi)
{}

StrategyCGI::StrategyCGI(StrategyCGI const & src) :
IResponseStrategy(),
_cgi(src._cgi), 
_request(src._request)
{
	
}

StrategyCGI::~StrategyCGI(void)
{
	
}

StrategyCGI &	StrategyCGI::operator=(StrategyCGI const & rhs)
{
	if (this != &rhs)
	{
		_cgi = rhs._cgi;
		_request =  rhs._request;
	}
	return *this;
}

Response *
StrategyCGI::create(Client & client)
{
	Response *	response		= new Response();
	Message *	response_cgi	= 0;

	this->_prepare(client);
	_request.set_body(client.get_request().get_body());
	// _request.debug();
	try
	{
		response_cgi = _request.send(client.get_full_path());
		response->set_code(200);
		response->add_header("Content-Type", response_cgi->get_header("Content-Type"));
		response->set_body(response_cgi->get_body());
		if (response_cgi->has_header("Status"))
			handle_status(*response_cgi, *response, client.get_server());
		delete (response_cgi);
	}
	catch(const std::exception& e)
	{

		std::cerr << "Bad CGI Response" << std::endl;
		response->set_error(500, client.get_server().get_path_error_page());
	}
	// response->debug();
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
		catch(const std::exception& e)
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

	if (request_http.get_body().length() == 0 || !request_http.has_header("Content-Length")){
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
	// _request.debug();
}
