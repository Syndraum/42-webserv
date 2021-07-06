/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BuilderCore.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 17:04:45 by mchardin          #+#    #+#             */
/*   Updated: 2021/07/02 15:25:16 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Core.hpp"
#include <cctype>

class BuilderCore
{
	private:

		size_t			_idx;
		std::string		_line;
		Core			*_core;
		std::string		_error_msg;

		void			skip_whitespaces();
		void			skip_comments();
		int				line_count();
		void			parse_server_port(Server *server);
		void			parse_server_name(Server *server);
		void			parse_server_root(Server *server);
		void			parse_server_path_error_page(Server *server);
		void			parse_server_auto_index(Server *server);
		void			parse_server_client_max_body_size(Server *server);
		void			parse_server();
		void			parse_worker();
		int				stoi_skip_number();

	public:
	
		BuilderCore(std::istream &fd, Core *core);
		~BuilderCore();
		void			print_debug() const; //tmp
		Core *			get_builded_core() const;
		void			parse_mine_type();
	
		class ParsingError : public std::exception
		{
				virtual const char*	what() const throw(){
					return ("Parsing Error");
			}
		};
};
