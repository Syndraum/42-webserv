#ifndef MESSAGE
# define MESSAGE

# include <map>
# include <string>

class Message
{
protected:
	std::map<std::string, std::string>		_headers;
	bool									_header_lock;
	std::string								_body;
	bool									_body_lock;
public:

	Message(void);
	Message(Message const & src);
	virtual ~Message(void);
	Message &	operator=(Message const &rhs);

	std::string const &						get_header(std::string const &key);
	bool									get_header_lock() const;
	const std::string &						get_body() const;
	bool									get_body_lock() const;
	Message &								add_header(const std::string & , const std::string &);
	void									set_header_lock(bool);
	void									set_body(const std::string &);
	void									set_body_lock(bool);
	void									lock_header();
	void									lock_body();

};

#endif
