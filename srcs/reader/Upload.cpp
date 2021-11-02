#include "Upload.hpp"

Upload::Upload(AReaderFileDescriptor & reader) : 
_reader(reader),
_state(FIND),
_boundary(),
_buffer(),
_n_buffer(),
_chunck(),
_position(0)
{}

Upload::Upload(Upload const & src) :
_reader(src._reader)
{
	*this = src;
}

Upload::~Upload(void)
{
	
}

Upload &
Upload::operator=(Upload const & rhs)
{
	if (this != &rhs)
	{
		_reader = rhs._reader;
		_state = rhs._state;
		_boundary = rhs._boundary;
		_buffer = rhs._buffer;
		_n_buffer = rhs._n_buffer;
		_chunck = rhs._chunck;
		_position= rhs._position;
	}
	return *this;
}

void
Upload::upload(Server & server, const Request & request)
{
	set_boundary(request);
	std::cout << "Boundary : " << _boundary << std::endl;
	_reader.fill_buffer();
	_buffer = _reader.get_buffer();
	debug();
	// switch (_state)
	// {
	// case FIND:
	// 	find();
	// 	break;
	// case HEADER:

	
	// default:
	// 	break;
	// }
	find();
	(void)server;
}

void
Upload::set_boundary(const Request & request)
{
	std::string	content_type	= request.get_header("Content-type");
	size_t		p_bound			= content_type.find("boundary");
	size_t		p_egal;

	if (p_bound != std::string::npos)
	{
		p_egal = content_type.find('=', p_bound);
		_boundary = "--" + content_type.substr(p_egal + 1);
	}
}

void
Upload::next_bound()
{
	_buffer = _buffer.substr(_position + _boundary.size());
}

void
Upload::find()
{
	if ((_position = _buffer.find(_boundary)) != std::string::npos)
	{
		// std::cout << "FIND boundary : " << _position << std::endl;
		// if (_state == WRITE){
		// }
		next_bound();
		_state = HEADER;
		debug();
	}
}

void
Upload::debug()
{
	std::cout << "BUFFER ----|" << _buffer << "|----" << std::endl;
}