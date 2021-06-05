/* source: https://www.binarytides.com/socket-programming-c-linux-tutorial/ */
//#include<stdio.h> //printf
//#include<string.h> //strcpy
//#include<sys/socket.h>
//#include<netdb.h>	//hostent
//#include<arpa/inet.h>
//
//int main(int argc , char *argv[])
//{
//	char *hostname = "www.google.com";
//	char ip[100];
//	struct hostent *he;
//	struct in_addr **addr_list;
//	int i;
//
//	if ( (he = gethostbyname( hostname ) ) == NULL)
//	{
//		//gethostbyname failed
//		herror("gethostbyname");
//		return 1;
//	}
//
//	//Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
//	addr_list = (struct in_addr **) he->h_addr_list;
//
//	for(i = 0; addr_list[i] != NULL; i++)
//	{
//		//Return the first one;
//		strcpy(ip , inet_ntoa(*addr_list[i]) );
//	}
//
//	printf("%s resolved to : %s\n" , hostname , ip);
//	//return 0;
//
//	(void)argc;
//	(void)argv;
//	int socket_desc;
//	struct sockaddr_in server;
//	char *message , server_reply[10000];
//	
//	//Create socket
//	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
//	if (socket_desc == -1)
//	{
//		printf("Could not create socket");
//	}
//		
//	server.sin_addr.s_addr = inet_addr(ip);
//	server.sin_family = AF_INET;
//	server.sin_port = htons( 80 );
//
//	//Connect to remote server
//	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
//	{
//		puts("connect error");
//		return 1;
//	}
//	
//	puts("Connected\n");
//	
//	//Send some data
//	message = "GET / HTTP/1.1\r\n\r\n";
//	if( send(socket_desc , message , strlen(message) , 0) < 0)
//	{
//		puts("Send failed");
//		return 1;
//	}
//	puts("Data Send\n");
//	
//	//Receive a reply from the server
//	if( recv(socket_desc, server_reply , 10000 , 0) < 0)
//	{
//		puts("recv failed");
//	}
//	puts("Reply received\n");
//	puts(server_reply);
//	
//	return 0;
//}

char response[] = 
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html><html><head><title>Bye-bye baby bye-bye</title>"
"<style>body { background-color: #111 }"
"h1 { font-size:4cm; text-align: center; color: black;"
" text-shadow: 0 0 2mm red}</style></head>"
"<body><h1>Goodbye, world!</h1></body></html>\r\n";

/* source: https://www.binarytides.com/socket-programming-c-linux-tutorial/ */
#include<stdio.h>
#include<string.h>	//strlen
#include<stdlib.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write

#include<pthread.h> //for threading , link with lpthread
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void *connection_handler(void *);
char *strjoin(char *str1, char *str2);

int main()
{
	int socket_desc , new_socket , c , one = 1;
	struct sockaddr_in server , client;

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
		printf("Could not create socket");

	//Set option on socket_fd (like REUSEADDR to rebind (and so, re-test quickly))
	setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );

	//Bind socket to ip addr
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("bind failed");
		return 1;
	}
	puts("bind done");

	//Listen
	listen(socket_desc , 3);

	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
	{
		puts("---- ---- ---- Connection accepted ---- ---- ----");

		int read_size, length; //recv return value, i think i like read (read the fucking manual)
		char client_message[2000], answer[10000], *header, *response;

		response = malloc(10000);
		if( (read_size = recv(new_socket , client_message , 2000 , 0)) > 0 )
		{
			printf("---- read_size: %d ----\n", read_size);

			client_message[read_size] = 0;
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
			int end = read(file_fd, answer, 10000);
			answer[end] = 0;

			header = strjoin(header, answer);
			header = strjoin(header, "\r\n");

			//printf("header: \n%s\n", header);
			close(file_fd);
			length = strlen(header);
			response = header;

			write(1, response, length);
			send(new_socket, response, length, 0);
			close(new_socket);
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

/* https://www.rosettacode.org/wiki/Hello_world/Web_server */
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include <arpa/inet.h>
//#include <err.h>
//
//char response[] = "HTTP/1.1 200 OK\r\n"
//"Content-Type: text/html; charset=UTF-8\r\n\r\n"
//"<!DOCTYPE html><html><head><title>Bye-bye baby bye-bye</title>"
//"<style>body { background-color: #111 }"
//"h1 { font-size:4cm; text-align: center; color: black;"
//" text-shadow: 0 0 2mm red}</style></head>"
//"<body><h1>Goodbye, world!</h1></body></html>\r\n";
//
//int main()
//{
//	int					one = 1;
//	int					client_fd;
//	struct sockaddr_in	server_address;
//	struct sockaddr_in	client_address;
//	socklen_t			socket_in_length = sizeof(client_address);
//
//	// get socket fd
//	int sock = socket(AF_INET, SOCK_STREAM, 0);
//	if (sock < 0)
//		err(1, "can't open socket");
//
//
//	// set socket option	
//	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
//
//
//	// set server port and ip, values, etc
//	int port = 8888;
//	server_address.sin_family = AF_INET;
//	server_address.sin_addr.s_addr = INADDR_ANY;
//	server_address.sin_port = htons(port);
//
//
//	// bind socket_fd to addr value
//	if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
//		close(sock);
//		err(1, "Can't bind");
//	}
//
//
//	// make socket_fd listen and can use accept on it
//	listen(sock, 5); // the second argument is max_queue_client
//
//
//	// while loop cause be want our server loop for ever
//	while (1) {
//		// get client fd, fullfill client_address struct
//		client_fd = accept(sock, (struct sockaddr *) &client_address, &socket_in_length);
//		printf("got connection\n");
//
//		if (client_fd == -1) {
//			perror("Can't accept");
//			continue;
//		}
//
//		// write on client_fd 
//		write(client_fd, response, sizeof(response) - 1); /*-1:'\0'*/
//		close(client_fd);
//	}
//}
