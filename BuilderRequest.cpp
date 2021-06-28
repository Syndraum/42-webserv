#include "BuilderRequest.hpp"

BuilderRequest::BuilderRequest(void) : _request(new Request()) {}

BuilderRequest::BuilderRequest(BuilderRequest const & src)
{
	*this = src;
}

BuilderRequest::~BuilderRequest(void)
{
	delete _request;
}

BuilderRequest &	BuilderRequest::operator=(BuilderRequest const & rhs)
{
	if (this != &rhs)
		;
	return *this;
}

int		BuilderRequest::add_method(std::string line)
{
	if (!line.compare(0, 4, "GET "))
	{
		// _request->set_method(GET);
		return (4);
	}
	else if (!line.compare(0, 5, "POST "))
	{
		// _request->set_method(POST);
		return (5);
	}
	else if (!line.compare(0, 7, "DELETE "))
	{
		// _request->set_method(DELETE);
		return (7);
	}
	else
		throw MethodNotImplemented();
}

int		BuilderRequest::add_path(std::string line)
{
	size_t		len = line.find(' ');
	if (len == std::string::npos)
		throw BadResquest();
	_request->set_path(line.substr(0, len));
	// check characters
	return(len + 1);
}

int		BuilderRequest::add_version(std::string line)
{
	if (line.compare(0, 8, VERSION))
		throw BadHttpVesion();
	_request->set_version(VERSION);
	return (8);
}

void	BuilderRequest::first_line(std::string line)
{
	int	j = add_method(line);
	j += add_path(&line[j]);
	j += add_version(&line[j]);
	if (line[j] != '\r')
		throw BadResquest();
}

void	BuilderRequest::parse_headers(std::string line)
{
	size_t		len = line.find(": ");

	if (line[line.length() - 1] != '\r' || len == std::string::npos || line[len - 1] == ' ')
		throw BadResquest();
	_request->add_header(std::pair<std::string, std::string>(line.substr(0, len), line.substr(len + 2, line.length() - len - 3)));
}

void	BuilderRequest::parse_request(std::istream &fd)
{
	std::string		line;
	bool			is_first_line = true;

	while(getline(fd, line))
	{
		//check printable characters
		if (is_first_line)
		{
			first_line(line);
			is_first_line = false;
		}
		else
			parse_headers(line);
	}
}

Request * BuilderRequest::get_request() const
{
	return _request;
}

void	BuilderRequest::reset()
{
	_request = new Request();
}