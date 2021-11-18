/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringPP.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:38:15 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/18 14:38:15 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_PP_HPP
# define STRING_PP_HPP

# include <string>
# include <sstream>
# include <algorithm>
# include <iostream>

class StringPP
{
	std::string m_string;
public:

	StringPP(void);
	StringPP(StringPP const & src);
	virtual ~StringPP(void);
	StringPP &	operator=(StringPP const &rhs);
	StringPP &	operator=(std::string const &rhs);

	std::string &	str();
	template <typename T>
	std::string &	replace_all(const std::string & search, T & replace)
	{
		std::stringstream ss;

		ss << replace;
		replace_all(search, ss.str());
		return (m_string);
	}
	std::string &		replace_all(const std::string & search, const std::string & replace);
	char *				string_copy() const;
	static	void		to_lower(std::string &);
	static std::string	to_lower(const std::string &);
	static	void		to_upper(std::string &);
	static std::string	to_upper(const std::string &);
	static std::string	extract_between(const std::string &, std::string);

};

#endif
