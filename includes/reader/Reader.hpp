/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/28 18:51:39 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_HPP
# define READER_HPP

# include <string>
# include <fstream>
# include <iostream>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

class Reader
{
	protected:

		std::string		_path;
		std::ifstream	_ifs;
		int				_length;
		std::string		_line;

	public:

		Reader(void);
		Reader(const std::string &);
		Reader(Reader const & src);
		virtual ~Reader(void);
		Reader &		operator=(Reader const &rhs);

		void			open();
		void			to_string(std::string & );
		void			close();
		void			get_line();

		std::ifstream &	get_ifs();
		int				get_length() const;
		void			set_length();
		std::string		get_buffer();
		bool			finished() const;
};

#endif
