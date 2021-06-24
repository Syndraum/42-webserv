#ifndef BUILDERREQUEST
# define BUILDERREQUEST

# include "Request.hpp"

class BuilderRequest
{
public:

	BuilderRequest(void);
	BuilderRequest(BuilderRequest const & src);
	virtual ~BuilderRequest(void);
	BuilderRequest &	operator=(BuilderRequest const &rhs);

	int		add_method(std::string line);
	int		add_path(std::string line);
	int		add_version(std::string line);
	int		first_line(std::string line);
	int		parse_headers(std::string line);
	int		parse_request(std::istream &fd);
	Request * get_request() const;
	void	reset();
private:
	Request	*	_request;
};

#endif
