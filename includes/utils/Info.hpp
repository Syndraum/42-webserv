/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Info.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:38:12 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 21:15:30 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_HPP
# define INFO_HPP

# include <string>

class Info
{
	public:

		static const std::string	server_name;
		static const std::string	version;
		static const std::string	http_revision;
		static const std::string	cgi_revision;
		static const std::string	path_config_file;
		static char **				env;

		Info(void);
		virtual ~Info(void);
};

#endif
