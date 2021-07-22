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
StrategyCGI::create(Server & server, Request & request)
{
	Response * response = 0;

	this->_prepare(server, request);
	_request.debug();
	_request.send();
	response = new Response();
	response->set_error(418);
	return (response);
}

void
StrategyCGI::_prepare(Server & server, Request & request)
{
	_request.add_header("AUTH_TYPE", "");
	if (request.get_body().length() != 0){
		_request.add_header("CONTENT_LENGTH", 0);
		if (request.has_header("Content-Type"))
			_request.add_header("CONTENT_TYPE", request.get_header("Content-Type"));
	}
	_request.add_header("GATEWAY_INTERFACE", Info::cgi_revision);
	_request.add_header("PATH_INFO", request.get_uri().get_extra_path());
	if (_request.get_header("PATH_INFO") != "")
		_request.add_header("PATH_TRANSLATED", server.get_full_path(request.get_uri().get_extra_path()));
	_request.add_header("QUERY_STRING", request.get_uri().get_query_string());
	_request.add_header("REMOTE_ADDR", "0.0.0.0"); // TMP
	_request.add_header("REMOTE_HOST", "");
	_request.add_header("REQUEST_METHOD", request.get_method()->get_name());
	_request.add_header("SCRIPT_NAME", request.get_uri().get_path());
	_request.add_header("SCRIPT_FILENAME", server.get_full_path(request.get_uri().get_path())); //PHP
	_request.add_header("SERVER_NAME", "0.0.0.0"); // TMP
	_request.add_header("SERVER_PORT", 8081);
	_request.add_header("SERVER_PROTOCOL", Info::http_revision);
	_request.add_header("SERVER_SOFTWARE", Info::server_name + "/" + Info::version);
}
