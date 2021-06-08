#include "cdai_test.h"

char *build_response(char *file_name)
{
	char *response;
	char read_char[10000];
	char *to_free;

	// we have to do th header
	char *header =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html; charset=UTF-8\r\n\r\n";

	// find a better way to find a file ?
	int file_fd = open(file_name, O_RDONLY);
	if (file_fd == -1)
	{
//		close(new_socket);
		return NULL;
	}

	// find a way to read and send chunk ?
	int end = read(file_fd, read_char, 10000);
	read_char[end] = 0;

	response = strjoin(header, read_char);

	to_free = response;
	// needed as reponse's end
	response = strjoin(to_free, "\r\n");
	free(to_free);

	close(file_fd); // open below

	return response;
}
