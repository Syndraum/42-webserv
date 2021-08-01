#ifndef ARRAY
# define ARRAY

# include <exception>
# include <cstring>
# include <iostream>

class Array
{
	char**		_data;
	size_t		_size;
	size_t		_capacity;

public:

	Array(void);
	Array(size_t capacity);
	Array(Array const & src);
	virtual ~Array(void);
	Array &	operator=(Array const &rhs);

	void	set_capacity(size_t capacity);
	char ** data() const;
	size_t	size() const;
	static size_t	len(char ** array);
	void	push_back(const char * value);
	void	clear();
};

#endif
