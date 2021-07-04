#ifndef EXTENSION
# define EXTENSION

# include <string>
# include <exception>

class Extension
{
public:

	Extension(void);
	Extension(Extension const & src);
	virtual ~Extension(void);
	Extension &	operator=(Extension const &rhs);

	static std::string	get_extention(const std::string & path);
	static std::string	get_mine_type(const std::string & ext);
private:

};

#endif
