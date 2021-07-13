#ifndef INFO
# define INFO

# include <string>

class Info
{
public:

	Info(void);
	virtual ~Info(void);

	static std::string	server_name();
	static std::string	version();
private:

};

#endif
