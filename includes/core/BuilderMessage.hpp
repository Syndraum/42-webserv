/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuilderMessage.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:36:22 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 21:09:11 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_MESSAGE_HPP
# define BUILDER_MESSAGE_HPP

# include "Message.hpp"
# include <exception>

class BuilderMessage
{
	protected:

		Message *	_message;

	public:

		BuilderMessage(void);
		BuilderMessage(BuilderMessage const & src);
		virtual ~BuilderMessage(void);
		BuilderMessage &	operator=(BuilderMessage const &rhs);

		Message *				get_message() const;
		virtual void			set_message(Message *);
		void					_parse_headers(std::string line);

		class BadRequest : public std::exception
		{
			virtual const char*	what() const throw(){
				return "Bad Request";
			}
		};
};

#endif
