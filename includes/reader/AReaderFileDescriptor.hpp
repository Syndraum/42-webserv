/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AReaderFileDescriptor.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:11:35 by cdai              #+#    #+#             */
/*   Updated: 2021/07/28 18:51:12 by mchardin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AREADER_FILE_DESCRIPTOR_HPP
# define AREADER_FILE_DESCRIPTOR_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <unistd.h>
# include <cstring>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 127
# endif

class AReaderFileDescriptor
{
	protected:
		int		_fd;
		char	_buffer[BUFFER_SIZE];

		AReaderFileDescriptor(void);

	public:
		AReaderFileDescriptor(int fd);
		AReaderFileDescriptor(AReaderFileDescriptor const &);
		virtual ~AReaderFileDescriptor(void);
		AReaderFileDescriptor const & operator=(AReaderFileDescriptor const &);

		int			get_next_line(std::string &);
		void		read_body(std::string &, int);
		void		read_until_end(std::string &);
		int			get_fd(void);
		void		set_fd(int);
		std::string	get_buffer(void) const;
		void		_reset_buffer(void);
		virtual int	_read(int n_read = BUFFER_SIZE - 1) = 0;
		std::string	get_next_buffer(void);
		void		write_body(int fd);
};

#endif
