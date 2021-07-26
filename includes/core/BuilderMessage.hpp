#ifndef BUILDERMESSAGE
# define BUILDERMESSAGE

# include "Message.hpp"
# include <exception>

class BuilderMessage
{
protected:
	Message *	_message;

	void					_parse_headers(std::string line);
public:

	BuilderMessage(void);
	BuilderMessage(BuilderMessage const & src);
	virtual ~BuilderMessage(void);
	BuilderMessage &	operator=(BuilderMessage const &rhs);

	Message *				get_message() const;
	virtual void			set_message(Message *);

	class BadRequest : public std::exception
	{
		virtual const char*	what() const throw(){
			return "Bad Request";
		}
	};
};

#endif
