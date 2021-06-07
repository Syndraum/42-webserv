char response[] = 
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html><html><head><title>Bye-bye baby bye-bye</title>"
"<style>body { background-color: #111 }"
"h1 { font-size:4cm; text-align: center; color: black;"
" text-shadow: 0 0 2mm red}</style></head>"
"<body><h1>Goodbye, world!</h1></body></html>\r\n";

/* source: https://www.binarytides.com/socket-programming-c-linux-tutorial/ */
//#include<stdio.h>
//#include<string.h>	//strlen
//#include<stdlib.h>	//strlen
//#include<sys/socket.h>
//#include<arpa/inet.h>	//inet_addr
//#include<unistd.h>	//write
//
//#include<pthread.h> //for threading , link with lpthread
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <sys/select.h>

#include "cdai_test.h"

char *strjoin(char *str1, char *str2);

int main()
{
	int socket_desc , new_socket , c;
//	int socket_desc , new_socket , c ,one = 1;
	struct sockaddr_in server , client;



//	//Create socket
//	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
//	if (socket_desc == -1)
//		printf("Could not create socket");
//
//	//Set option on socket_fd (like REUSEADDR to rebind (and so, re-test quickly))
//	setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
	socket_desc = get_new_socket();



	//Prepare the sockaddr_in structure
//	server.sin_family = AF_INET;
//	server.sin_addr.s_addr = INADDR_ANY;
//	server.sin_port = htons( 8888 );
	init_server(&server);



	//Bind socket to ip addr
//	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
//	{
//		puts("bind failed");
//		return 1;
//	}
//	puts("bind done");
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
		char client_message[2000], answer[10000], *header, *response, *to_free;

		response = malloc(10000);

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
			header =
				"HTTP/1.1 200 OK\r\n"
				"Content-Type: text/html; charset=UTF-8\r\n\r\n";

			int file_fd = open("index.html", O_RDONLY);
			if (file_fd == -1)
			{
				free(response);
				close(new_socket);
				break;
			}
			int end = read(file_fd, answer, 10000);
			answer[end] = 0;

			to_free = header;
			header = strjoin(header, answer);

			to_free = header;
			header = strjoin(header, "\r\n");
			free(to_free);

			//printf("header: \n%s\n", header);
			close(file_fd);
			length = strlen(header);
			to_free = response;
			response = header;
			free(to_free);

			write(1, response, length);
			send(new_socket, response, length, 0);
			close(new_socket);
			free(header);
		}

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

char *strjoin(char *str1, char *str2)
{
	char *res = malloc(strlen(str1) + strlen(str2) + 1);
	for (unsigned long i = 0; i < strlen(str1); i++)
		res[i] = str1[i];
	for (unsigned long i = 0; i < strlen(str2); i++)
		res[strlen(str1) + i] = str2[i];
	res[strlen(str1) + strlen(str2) + 1] = 0;

	return res;
}
