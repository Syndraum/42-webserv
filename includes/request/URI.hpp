/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   URI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:37:35 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 18:08:12 by syndraum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef URI_HPP
# define URI_HPP

#include <string>
#include <sstream>

// debug
#include <iostream>

class URI
{
	std::string		_content;
	std::string		_scheme;
	std::string		_server_name;
	std::string		_port;
	std::string		_path;
	std::string		_extra_path;
	std::string		_query_string;

public:

	URI(void);
	URI(const std::string & uri);
	URI(URI const & src);
	virtual ~URI(void);
	URI &	operator=(URI const &rhs);

	const std::string & get_scheme() const;
	const std::string & get_server_name() const;
	const std::string & get_port() const;
	const std::string & get_path() const;
	const std::string & get_extra_path() const;
	const std::string & get_query_string() const;

	void	set_uri(const std::string &);
	size_t	find_percent(const std::string &) const;
	char	get_next_percent(const std::string &) const;
	void	convert(std::string & str);
	void	debug() const;
private:

};

#endif
