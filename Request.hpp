#ifndef REQUEST_HPP
# define REQUEST_HPP

# define GET 0
# define POST 1
# define DELETE 2

# define VERSION "HTTP/1.1"

# include "includes.hpp"

using namespace std;

class Request
{
private:
	int						_method;
	string					_path;
	string					_version;
	int						_response_code;
	map<string, string>		_headers;


	string	_error_msg(int code);
	int		_return_error(string msg);
	int		_set_method(string line);
	int		_set_path(string line);
	int		_set_version(string line);
	int		_first_line(string line);
	int		_parse_headers(string line);
	/* data */
public:
	Request(/* args */);
	~Request();

	int		parsing();
	void	print_debug();
};

#endif