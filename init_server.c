#include "cdai_test.h"

void init_server(struct sockaddr_in *server)
{
	server->sin_family = AF_INET;
	server->sin_addr.s_addr = INADDR_ANY;
	server->sin_port = htons( 8888 );
}
