/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AReaderFileDescriptor.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syndraum <syndraum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:11:35 by cdai              #+#    #+#             */
/*   Updated: 2021/11/03 14:02:56 by syndraum         ###   ########.fr       */
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
# include <exception>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

class AReaderFileDescriptor
{
	protected:
		int		_fd;
		size_t	_size;
		char	_buffer[BUFFER_SIZE];

		AReaderFileDescriptor(void);

	public:
		class OutOfBound : public std::exception
		{
			virtual const char* what() const throw(){
				return "Out of Bound";
			}
		};
		class OutOfBuffer : public std::exception
		{
			virtual const char* what() const throw(){
				return "Out of Buffer";
			}
		};
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
		virtual int	_read(void *, int n_read = BUFFER_SIZE - 1) = 0;
		int			next_read(size_t size = BUFFER_SIZE - 1);
		int			fill_buffer();
		// std::string	get_next_buffer(int index = BUFFER_SIZE - 1);
		void		write_body(int fd);
};

#endif
