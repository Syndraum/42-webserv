#ifndef UPLOAD
# define UPLOAD

# include <string>
# include "Request.hpp"
# include "AReaderFileDescriptor.hpp"
# include "Server.hpp"

class Upload
{
public:
	enum e_state{
		FIND,
		WRITE,
		END,
	};

private:

	AReaderFileDescriptor &	_reader;

	Upload::e_state			_state;
	std::string				_boundary;
	std::string				_buffer;
	std::string				_n_buffer;
	std::string				_chunck;
	size_t					_position;

public:

	Upload(AReaderFileDescriptor &);
	Upload(Upload const & src);
	virtual ~Upload(void);
	Upload &	operator=(Upload const &rhs);

	void	upload(Server &, const Request &);
	void	set_boundary(const Request &);
};

#endif
