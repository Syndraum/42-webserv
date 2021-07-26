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
	Response * response = 0;

	this->_prepare(client);
	_request.debug();
	int std_out = _request.send(client.get_full_path());


//	ReaderFileDescriptor reader(std_out);
//	std::string line;
//	reader.get_next_line(line);
//	std::cout << "line : " << line << std::endl;
//	reader.get_next_line(line);
//	std::cout << "line : " << line << std::endl;
//	reader.get_next_line(line);
//	std::cout << "line : " << line << std::endl;


	response = new Response();
//	response->set_error(418);
	response->set_code(200);

	HandlerResponseCGI _handler(std_out);
	_handler.set_response(response);

	_handler.parse();
	response->debug();
	return (response);
}

void
StrategyCGI::_prepare(Client & client)
{
	// Request &	request_http	= client.get_request();
	// Server &	server			= client.get_server();

	(void)client;
	// if (request_http.get_body().length() != 0){
	// 	_request.add_header("CONTENT_LENGTH", 0);
	// 	if (request_http.has_header("Content-Type"))
	// 		_request.add_header("CONTENT_TYPE", request_http.get_header("Content-Type"));
	// }
	// if (_request.get_header("PATH_INFO") != "")
	// 	_request.add_header("PATH_TRANSLATED", server.get_full_path(request_http.get_uri().get_extra_path()));
	// _request
	// 	.add_header("AUTH_TYPE", "")
	// 	.add_header("GATEWAY_INTERFACE", Info::cgi_revision)
	// 	.add_header("PATH_INFO", request_http.get_uri().get_extra_path())
	// 	.add_header("QUERY_STRING", request_http.get_uri().get_query_string())
	// 	.add_header("REMOTE_ADDR", "0.0.0.0") // TMP
	// 	.add_header("REMOTE_HOST", "")
	// 	.add_header("REQUEST_METHOD", request_http.get_method()->get_name())
	// 	.add_header("SCRIPT_NAME", request_http.get_uri().get_path())
	// 	.add_header("SERVER_NAME", "0.0.0.0") // TMP
	// 	.add_header("SERVER_PORT", client.get_server_socket().get_port())
	// 	.add_header("SERVER_PROTOCOL", Info::http_revision)
	// 	.add_header("SERVER_SOFTWARE", Info::server_name + "/" + Info::version)
	// ;
	// _request.add_header("SCRIPT_FILENAME", server.get_full_path(request_http.get_uri().get_path())); //PHP
}
