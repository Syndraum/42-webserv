/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:36:25 by mchardin          #+#    #+#             */
/*   Updated: 2021/11/19 21:09:34 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ClientSocket.hpp"
# include "Server.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "IResponseStrategy.hpp"
# include "poll.h"

class IResponseStrategy;

class Client
{
	public:

		enum request_state {
			READ_HEADER,
			STRATEGY,
			SEND_RESPONSE,
			END
		};

	private:

		Request					_request;
		ClientSocket			_socket;
		Server *				_server;
		ServerSocket *			_server_socket;
		IResponseStrategy *		_strategy;
		Response *				_response;
		request_state			_state;
		short					_revent;
		bool					_close;

		Client(void);

	public:

		Client(Server &, ServerSocket &);
		Client(Client const & src);
		virtual ~Client(void);
		Client &	operator=(Client const &rhs);
		bool operator==(const Client & rhs) const
		{
			if (this->_socket.get_socket() == rhs._socket.get_socket())
				return (true);
			return (false);
		}

		Request &		get_request();
		Request const &	get_request() const;
		ClientSocket &	get_socket_struct();
		int				get_socket();
		Server &		get_server();
		Server const &	get_server() const;
		ServerSocket &	get_server_socket();
		Response *		get_response();
		std::string		get_full_path() const;
		request_state	get_state() const;
		void			set_state(request_state);
		void			set_server(Server *);
		void			set_server_socket(ServerSocket *);
		short			get_revent() const;
		void			set_revent(short);
		bool			get_close() const;
		void			set_close(bool);

		void	set_strategy(IResponseStrategy *);
		void	do_strategy(Client &);
		void	send(int fd);
		void	clean_reponse();

};

#endif
