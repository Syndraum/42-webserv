#ifndef PIPE
# define PIPE

#include <vector>

class Pipe
{
	std::vector<int>			_out;
	std::vector<int>			_err;
	std::vector<int>			_in;
public:

	Pipe(void);
	Pipe(Pipe const & src);
	virtual ~Pipe(void);
	Pipe &	operator=(Pipe const &rhs);
	int *	get_out();
	int *	get_err();
	int *	get_in();

};

#endif
