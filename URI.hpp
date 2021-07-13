#ifndef URI_H
# define URI_H

#include <string>

// debug
#include <iostream>

class URI
{
	std::string		_content;
	std::string		_scheme;
	std::string		_server_name;
	std::string		_port;
	std::string		_path;
	std::string		_extra_path;
	std::string		_query_string;

public:

	URI(void);
	URI(const std::string & uri);
	URI(URI const & src);
	virtual ~URI(void);
	URI &	operator=(URI const &rhs);

	void	set_uri(const std::string &);
	void	debug() const;
private:

};

#endif
