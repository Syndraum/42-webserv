/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CoreBuilder.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:04:45 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/25 18:07:55 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"
#include <cctype>

class CoreBuilder
{
	private:

		size_t		_idx;
		std::string	_line;
		Core		*_core;

		void	skip_whitespaces();
		void	skip_comments();
		void	parse_server_port(Server *server);
		void	parse_server_string(Server *server, int directive_len, void (*setter)(std::string));
		void	parse_server_autoindex(Server *server)
		void	parse_server_body_size(Server *server)
		void	parse_server();
		void	parse_worker();

	public:
		CoreBuilder(std::istream fd, Core *core);
		~CoreBuilder();
		Core	*get_builded_core() const;
};
