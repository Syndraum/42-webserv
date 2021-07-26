#ifndef INFO
# define INFO

# include <string>

class Info
{
public:

	static const std::string	server_name;
	static const std::string	version;
	static const std::string	http_revision;
	static const std::string	cgi_revision;
	static const std::string	path_config_file;
	static char **				env;

	Info(void);
	virtual ~Info(void);

private:

};

#endif
