/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AReaderFileDescriptor.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:11:35 by cdai              #+#    #+#             */
/*   Updated: 2021/07/23 11:47:19 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AREADER_FILE_DESCRIPTOR
#define AREADER_FILE_DESCRIPTOR

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

class AReaderFileDescriptor
{
	protected:
		int		_fd;
		char	_buffer[BUFFER_SIZE];

		AReaderFileDescriptor(void);
		void	_reset_buffer(void);


	public:
		AReaderFileDescriptor(int fd);
		AReaderFileDescriptor(AReaderFileDescriptor const &);
		virtual ~AReaderFileDescriptor(void);
		AReaderFileDescriptor const & operator=(AReaderFileDescriptor const &);

		virtual int	get_next_line(std::string & line) = 0;
}

#endif
