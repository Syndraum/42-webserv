/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchardin <mchardin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:58:40 by mchardin          #+#    #+#             */
/*   Updated: 2021/06/08 19:47:38 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <isotream>
//#include <string>
//
//int		main()
//{
//	;
//}

#include <poll.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
} while (0)

	int
main(int argc, char *argv[])
{
	int nfds, num_open_fds;
	struct pollfd *pfds;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s file...\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	num_open_fds = nfds = argc - 1;
	// array of fd
	pfds = (struct pollfd*)calloc(nfds, sizeof(struct pollfd));
	if (pfds == NULL)
		errExit("malloc");

	/* Open each file on command line, and add it 'pfds' array. */
	for (int j = 0; j < nfds; j++) {
		pfds[j].fd = open(argv[j + 1], O_RDONLY & O_NONBLOCK);
		if (pfds[j].fd == -1)
			errExit("open");

		printf("Opened \"%s\" on fd %d\n", argv[j + 1], pfds[j].fd);

		pfds[j].events = POLLIN;
	}

	/* Keep calling poll() as long as at least one file descriptor is
	   open. */

	while (num_open_fds > 0) {
		// booleen
		int ready;

		printf("About to poll()\n");
		// blocking function
		ready = poll(pfds, nfds, -1);
		if (ready == -1)
			errExit("poll");

		// ready is the return of poll, can we deal with it as the index of the fd ?
		printf("Ready: %d\n", ready);

		/* Deal with array returned by poll(). */
		for (int j = 0; j < nfds; j++) {
			char buf[10];

			// revents 0 is not ready to read or write
			if (pfds[j].revents != 0) {
				printf("  fd=%d; events: %s%s%s\n", pfds[j].fd,
						(pfds[j].revents & POLLIN)  ? "POLLIN "  : "",
						(pfds[j].revents & POLLHUP) ? "POLLHUP " : "",
						(pfds[j].revents & POLLERR) ? "POLLERR " : "");

				if (pfds[j].revents & POLLIN) {
					ssize_t s = read(pfds[j].fd, buf, sizeof(buf));
					if (s == -1)
						errExit("read");
					printf("    read %zd bytes: %.*s\n",
							s, (int) s, buf);
//					if (s == 0) {
//					printf("    closing fd %d\n", pfds[j].fd);
//					if (close(pfds[j].fd) == -1)
//						errExit("close");
//					num_open_fds--;
//					}
				} else {                /* POLLERR | POLLHUP */
					printf("    closing fd %d\n", pfds[j].fd);
					if (close(pfds[j].fd) == -1)
						errExit("close");
					num_open_fds--;
				}
			}
		}
	}
	free(pfds);
	printf("All file descriptors closed; bye\n");
	exit(EXIT_SUCCESS);
}
