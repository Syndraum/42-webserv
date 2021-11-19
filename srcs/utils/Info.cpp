/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Info.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:35:49 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 21:21:56 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Info.hpp"

const std::string Info::server_name			= "Webserviette";
const std::string Info::version				= "4.2";
const std::string Info::http_revision		= "HTTP/1.1";
const std::string Info::cgi_revision		= "CGI/1.1";
const std::string Info::path_config_file	= "./config/default.conf";
char ** Info::env							= 0;

Info::Info(void){}

Info::~Info(void)
{}
