#include "Upload.hpp"

Upload::Upload(AReaderFileDescriptor * reader) :
_reader(reader),
_state(FIND),
_boundary(),
_buffer(),
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
		_position = rhs._position;
		_filename = rhs._filename;
		_message = rhs._message;
	}
	return *this;
}

Upload *
Upload::set_reader(AReaderFileDescriptor & reader)
{
	_reader = &reader;
	return (this);
}

void
Upload::upload(Server & server, const Request & request)
{
	if(_reader == 0)
		throw InvalidReader();
	// std::cout << "adress :" << this << std::endl;
	if (_boundary == "")
	{
		set_boundary(request);
		std::cout << "Boundary : " << _boundary << std::endl;
		std::cout << "state : " << _state << std::endl;
		_reader->fill_buffer();
		_buffer = _reader->get_buffer();
	}
	// debug();
	// while (_state != END)
	// {
		switch (_state)
		{
		case FIND:
			find();
			break;
		case HEADER:
			header(server);
			break;
		case WRITE:
			write();
			break;
		default:
			break;
		}
	// }
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
Upload::set_filename(const Message & message)
{
	std::string	header;
	size_t		position;

	if (!message.has_header("Content-Disposition"))
		throw std::exception();
	header = message.get_header("Content-Disposition");
	position = header.find("filename");
	if (position != std::string::npos)
		_filename = StringPP::extract_between(header.substr(position), "\"");
	else
		_filename = "unknow";
}

Upload::e_state
Upload::get_state() const
{
	return (_state);
}

void
Upload::next_position()
{
	if(_reader == 0)
		throw InvalidReader();
	_reader->next_read(_position);
	_buffer = _reader->get_buffer();
}

bool
Upload::find_bound()
{
	return ((_position = _buffer.find(_boundary)) != std::string::npos);
}

void
Upload::header(const Server & server)
{
	size_t position = 0;

	debug();
	while(_buffer[0] != '\r')
	{
		position = _buffer.find(": ");
		if (position == std::string::npos)
			throw BadMessage();
		_message.add_header(_buffer.substr(0, position), _buffer.substr(position + 2, _buffer.find('\n') - (position + 2)));
		_position = _buffer.find('\n') + 1;
		next_position();
		// debug();
	}
	_position = 2;
	next_position();
	_message.debug();
	debug();
	if (_message.has_header("Content-Type"))
	{
		set_filename(_message);
		std::cout << "filename : " << _filename << std::endl;
		_file.open((server.get_root() + "/" + server.get_upload_path() + "/" + _filename).c_str(), std::fstream::out | std::fstream::trunc);
		if ((_file.rdstate() & std::ifstream::failbit ) != 0)
    		throw std::exception(); // should catch to return error 500
		_state = WRITE;
	}
	else
		_state = FIND;
}

void
Upload::find()
{
	if (find_bound())
	{
		if (_buffer.find(_boundary + "--") == _position)
			_state = END;
		else
		{
			_position += _boundary.length() + 2;
			next_position();
			_state = HEADER;
		}
		// debug();
	}
}

void
Upload::write()
{
	// debug();
	if (find_bound())
	{
		// std::cout << "FIND - BOUND" << std::endl;
		_file << _buffer.substr(0, _position - 2);
		_file.close();
		_filename = "";
		_message.clear_header();
		_state = FIND;
	}
	else
	{
		// std::cout << "FIND - NOT BOUND" << std::endl;
		_position = _buffer.size() - _boundary.size();
		_file << _buffer.substr(0, _position);
		next_position();
	}
	
}

void
Upload::debug()
{
	std::cout << "BUFFER ~~~~|" << _buffer << "|~~~~" << std::endl;
}