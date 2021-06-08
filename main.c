/* source: https://www.binarytides.com/socket-programming-c-linux-tutorial/ */
#include "cdai_test.h"

int main()
{
	int socket_desc , new_socket , c;
	struct sockaddr_in server , client;



	//Create socket
	//Set option on socket_fd (like REUSEADDR to rebind (and so, re-test quickly))
	socket_desc = get_new_socket();



	//Prepare the sockaddr_in structure
	init_server(&server);



	//Bind socket to ip addr
	server_bind(socket_desc, &server);

	//Listen
	listen(socket_desc , 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("---- ---- ---- Connection accepted ---- ---- ----");

		int read_size, length; //recv return value, i think it's like read
		//char client_message[2000], answer[10000], *header, *response, *to_free;
		char client_message[2000], *response;

		// recv is a kind of read
		if( (read_size = recv(new_socket , client_message , 2000 , 0)) > 0 )
		{
			printf("---- read_size: %d ----\n", read_size);

			client_message[read_size] = 0;
			// print in stdout the request
			write(1, client_message , strlen(client_message));
		}


		// like ctrl + d, i think, or EOF
		if(read_size == 0)
		{
			puts("Client disconnected");
			fflush(stdout);
		} // handle recv error
		else if(read_size == -1)
			perror("recv failed");
		else
		{
			response = build_response("index.html");

			length = strlen(response);
			write(1, response, length);

			// do the same than write
			send(new_socket, response, length, 0);

			free(response);
			// if the socket is not closed, the broswer continue working
			close(new_socket);
		}

		// useless. Maybe we can handle signal ?
		if (!strcmp(client_message, "CLOSE\r\n"))
			break;

	}

	// handle accept() fail
	if (new_socket < 0)
	{
		perror("accept failed");
		return 1;
	}

	return 0;
}

