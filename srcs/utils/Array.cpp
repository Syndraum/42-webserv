#include "Array.hpp"

Array::Array(void) :
	_data(0),
	_size(0),
	_capacity(0)
{}

Array::Array(size_t capacity) :
	_data(new char *[capacity + 1]),
	_size(0),
	_capacity(capacity)
{
	_data[0] = 0;
}

Array::Array(Array const & src)
{
	*this = src;
}

Array::~Array(void)
{
	this->clear();
}

Array &
Array::operator=(Array const & rhs)
{
	if (this != &rhs)
	{
		_data = rhs._data;
		_size = rhs._size;
		_capacity = rhs._capacity;	
	}
	return (*this);
}

void
Array::set_capacity(size_t capacity)
{
	if (_capacity != 0)
		throw std::exception();
	_capacity = capacity;
	_data = new char *[_capacity + 1];
}

char **
Array::data() const
{
	return (_data);
}

size_t
Array::size() const
{
	return (_size);
}

size_t
Array::len(char ** array)
{
	size_t i = 0;
	
	while(array[i])
		i++;
	return (i);
}

void
Array::push_back(const char* str)
{
	size_t i	= -1;
	size_t len	= std::strlen(str);

	if (_size >= _capacity)
		throw std::exception();
	_data[_size] = new char[len + 1];
	while(++i < len)
		_data[_size][i] = str[i];
	_data[_size][i] = 0;
	_size++;
	_data[_size] = 0;
}

void
Array::clear()
{
	size_t i	= 0;

	if (_data == 0)
		return ;
	while (_data[i])
	{
		delete [] _data[i];
		i++;
	}
	delete [] _data;
	_data = 0;
}