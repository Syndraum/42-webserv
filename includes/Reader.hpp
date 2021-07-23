/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:50:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/01 15:50:41 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER
# define READER

# include <string>
# include <fstream>

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
};

#endif
