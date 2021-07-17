#include "URI.hpp"

URI::URI(void) :
_content(),
_scheme(),
_server_name(),
_port(),
_path(),
_extra_path(),
_query_string()
{}

URI::URI(const std::string & uri) :
_content(uri),
_scheme(),
_server_name(),
_port(),
_path(),
_extra_path(),
_query_string()
{
	set_uri(uri);
}

URI::URI(URI const & src)
{
	*this = src;
}

URI::~URI(void)
{
	
}

URI &
URI::operator=(URI const & rhs)
{
	if (this != &rhs) {
		this->_content = rhs._content;
		this->_scheme = rhs._scheme;
		this->_server_name = rhs._server_name;
		this->_port = rhs._port;
		this->_path = rhs._path;
		this->_extra_path = rhs._extra_path;
		this->_query_string = rhs._query_string;
	}
	return *this;
}

const std::string &
URI::get_scheme() const
{ return (_scheme); }

const std::string &
URI::get_server_name() const
{ return (_server_name); }

const std::string &
URI::get_port() const
{ return (_port); }

const std::string &
URI::get_path() const
{ return (_path); }

const std::string &
URI::get_extra_path() const
{ return (_extra_path); }

const std::string &
URI::get_query_string() const
{ return (_query_string); }

void
URI::set_uri(const std::string & uri)
{
	size_t index		= 0;
	size_t begin		= 0;
	size_t query_begin	= 0;

	_content = uri;
	index = _content.find("://", begin);
	if (index == std::string::npos)
		index = 0;
	else{
		_scheme = _content.substr(begin, index);
		begin = index + 3;
		index = _content.find("/", begin);
		_server_name = _content.substr(begin, index - begin);
		begin = index;
		index = _server_name.find(":", 0);
		if (index != std::string::npos){
			_port = _server_name.substr(index + 1, _server_name.length() - index);
			_server_name = _server_name.substr(0, index);
		}
		index = begin;
	}
	index = _content.find(".", begin);
	query_begin = _content.find("?", begin);
	if (query_begin == std::string::npos)
		query_begin = _content.length();
	if (index != std::string::npos){
		index = _content.find("/", index);
		if (index != std::string::npos){
			_path = _content.substr(begin, index - begin);
			_extra_path = _content.substr(index, query_begin - index);
		}
		else
			_path = _content.substr(begin, query_begin - begin);
	}
	else{
		_path = _content.substr(begin, query_begin - begin);
	}
	if (query_begin != _content.length())
		_query_string = _content.substr(query_begin + 1, _content.length() - query_begin);
	// debug();
}

void
URI::debug() const
{
	std::cout << " ~'~'~ URI ~'~'~ " << std::endl;
	std::cout << "content : " << _content << std::endl;
	std::cout << "scheme : " << _scheme << std::endl;
	std::cout << "server_name : " << _server_name << std::endl;
	std::cout << "port : " << _port << std::endl;
	std::cout << "path : " << _path << std::endl;
	std::cout << "extra_path : " << _extra_path << std::endl;
	std::cout << "query_string : " << _query_string << std::endl;
}