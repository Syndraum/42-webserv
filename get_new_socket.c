#include "cdai_test.h"

int get_new_socket(void)
{
	int	socket_fd;
	int one = 1;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1)
	{
		printf("error: could not create socket\n");
		return (-1);
	}

	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

	return socket_fd;
}
