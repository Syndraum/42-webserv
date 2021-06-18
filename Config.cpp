/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:26:17 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/18 18:40:02 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Config.hpp"

using namespace std;

Config::Config()
{}

Config::~Config()
{}

// void	Config::print_debug() //TMP
// {
// 	cerr << "METHOD CODE : " << _method << " PATH : \"" << _path << "\" " << _version << endl;
//     cerr << "HEADERS : " << endl;
    
//     map<string, string>::iterator ite = _headers.end();
//     for (map<string, string>::iterator it = _headers.begin(); it != ite; it++)
//         cout << "\"" << it->first << "\" - \"" << it->second << "\"" << endl;

// }

// string	Config::_error_msg(int code)
// {
// 	if (code == BAD_Config)
// 		return ("Bad Config");
// 	else if(code == BAD_VERSION)
// 		return ("HTTP Version Not Supported");
// 	else if(code == NOT_IMPLEMENTED)
// 		return("Not Implemented");
// 	return (0);
// }

// int		Config::_return_error(string msg) // msg = TMP
// {
// 	cout << _response_code << " " << _error_msg(_response_code) << " : " << msg << endl;
// 	return(_response_code);
// }

// int		Config::_set_method(string line)
// {
// 	if (!line.compare(0, 4, "GET "))
// 	{
// 		_method = GET;
// 		return (4);
// 	}
// 	else if (!line.compare(0, 5, "POST "))
// 	{
// 		_method = POST;
// 		return (5);
// 	}
// 	else if (!line.compare(0, 7, "DELETE "))
// 	{
// 		_method = DELETE;
// 		return (7);
// 	}
// 	else
// 	{
// 		_response_code = NOT_IMPLEMENTED;
// 		return (-1);
// 	}
// }

// int		Config::_set_path(string line)
// {
// 	size_t		len = line.find(' ');
// 	if (len == string::npos)
// 	{
// 		_response_code = BAD_Config;
// 		return(-1);
// 	}
// 	_path = line.substr(0, len);
// 	// check characters
// 	return(len + 1);
// }

// int		Config::_set_version(string line)
// {
// 	if (line.compare(0, 8, VERSION))
// 	{
// 		_response_code = BAD_VERSION;
// 		return (-1);
// 	}
// 	_version = VERSION;
// 	return (8);
// }

// int		Config::_first_line(string line)
// {
// 	int	j = _set_method(line);
// 	if (j < 0)
// 		return (_return_error("wrong method"));
// 	j += _set_path(&line[j]);
// 	if (j < 0)
// 		return (_return_error("wrong path"));
// 	j += _set_version(&line[j]);
// 	if (j < 0)
// 		return (_return_error("wrong version"));
// 	if (line[j] != '\r')
// 	{
// 		_response_code = BAD_Config;
// 		return (_return_error("")); //ERROR
// 	}
// 	return (OK);
// }

// int		Config::_parse_headers(string line)
// {
//     size_t		len = line.find(": ");

// 	if (line[line.length() - 1] != '\r' || len == string::npos || line[len - 1] == ' ')
// 	{
// 		_response_code = BAD_Config;
// 		return (_return_error("")); //ERROR
// 	}
//     _headers.insert(pair<string, string>(line.substr(0, len), line.substr(len + 2, line.length() - len - 3)));
// 	return (OK);
// }

// int		Config::parsing()
// {
// 	string						line;
// 	int							i;
//     int                         ret;

// 	i = 0;
// 	while(getline(cin, line))
// 	{
// 		if (i == 0)
//         {
//             ret = _first_line(line);
//             if (ret != OK)
//                 return(_response_code);
//         }
// 		else if (_parse_headers(line) != OK)
// 				return(_response_code);
// 		i++;
// 	}
// 	return(_response_code);
// }
