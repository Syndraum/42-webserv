#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <map>
# include <string>
# include <sstream>

# include <iostream> // TMP

class Message
{
public:
	typedef	std::map<std::string, std::string>	map;
protected:
	map										_headers;
	bool									_header_lock;
	std::string								_body;
	bool									_body_lock;
public:

	Message(void);
	Message(Message const & src);
	virtual ~Message(void);
	Message &	operator=(Message const &rhs);

	map const &									get_headers() const;
	std::string const &						get_header(std::string const &key);
	bool									get_header_lock() const;
	const std::string &						get_body() const;
	bool									get_body_lock() const;
	template <typename T>
	Message &								add_header(std::string name, T content)
	{
		std::stringstream ss;

		ss << content;
		return (add_header(name, ss.str()));
	}
	Message &								add_header(const std::string & , const std::string &);
	Message &								clear_header();
	bool									has_header(const std::string &);
	void									set_header_lock(bool);
	Message &								set_body(const std::string &);
	void									set_body_lock(bool);
	void									lock_header();
	void									lock_body();

	void	debug();

};

#endif
