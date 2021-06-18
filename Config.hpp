/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:26:21 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/18 18:37:39 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "includes.hpp"

using namespace std;

class Config
{
private:
	string					_name;
	vector<int>				_port;
	vector<int>				_socket;
	int						_bodySize;
	string	 				_pathErrorPage;
	vector<string>			_listMethod;
	string	 				_root;
	bool					_autoIndex;

	string	_error_msg(int code);
	int		_return_error(string msg);
	int		_set_index(string line);
	int		_set_body_size(string line);
	int		_set_port_n_socket(string line);
	int		_set_name(string line);
	int		_parse_server(string line);
public:
	Config();
	~Config();

	int		parsing();
	void	print_debug();
};

#endif