#include "cdai_test.h"

int server_bind(int fd, struct sockaddr_in *server)
{
	if( bind(fd, (struct sockaddr *)server , sizeof(*server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");
	
	return (0);
}
