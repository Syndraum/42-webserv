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

/* source: https://www.binarytides.com/socket-programming-c-linux-tutorial/ */
//#include<stdio.h>
//#include<string.h>	//strlen
//#include<stdlib.h>	//strlen
//#include<sys/socket.h>
//#include<arpa/inet.h>	//inet_addr
//#include<unistd.h>	//write
//
//#include<pthread.h> //for threading , link with lpthread
//
//void *connection_handler(void *);
//
//int main()
//{
//	int socket_desc , new_socket , c , *new_sock;
//	struct sockaddr_in server , client;
//	char *message;
//
//	//Create socket
//	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
//	if (socket_desc == -1)
//	{
//		printf("Could not create socket");
//	}
//
//	//Prepare the sockaddr_in structure
//	server.sin_family = AF_INET;
//	server.sin_addr.s_addr = INADDR_ANY;
//	server.sin_port = htons( 8888 );
//
//	//Bind
//	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
//	{
//		puts("bind failed");
//		return 1;
//	}
//	puts("bind done");
//
//	//Listen
//	listen(socket_desc , 3);
//
//	//Accept and incoming connection
//	puts("Waiting for incoming connections...");
//	c = sizeof(struct sockaddr_in);
//	while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
//	{
//		puts("Connection accepted");
//
//		//Reply to the client
//		message = "Hello Client , I have received your connection. And now I will assign a handler for you\n";
//		write(new_socket , message , strlen(message));
//
//		pthread_t sniffer_thread;
//		new_sock = malloc(1);
//		*new_sock = new_socket;
//
//		if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
//		{
//			perror("could not create thread");
//			return 1;
//		}
//
//		//Now join the thread , so that we dont terminate before the thread
//		//pthread_join( sniffer_thread , NULL);
//		puts("Handler assigned");
//	}
//
//	if (new_socket<0)
//	{
//		perror("accept failed");
//		return 1;
//	}
//
//	return 0;
//}
//
///*
// * This will handle connection for each client
// * */
//void *connection_handler(void *socket_desc)
//{
//	//Get the socket descriptor
//	int sock = *(int*)socket_desc;
//	int read_size;
//	char *message , client_message[2000];
//
//	//Send some messages to the client
//	message = "Greetings! I am your connection handler\n";
//	write(sock , message , strlen(message));
//
//	message = "Now type something and i shall repeat what you type \n";
//	write(sock , message , strlen(message));
//
//	//Receive a message from client
//	while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 )
//	{
//		//Send the message back to client
//		write(sock , client_message , strlen(client_message));
//	}
//
//	if(read_size == 0)
//	{
//		puts("Client disconnected");
//		fflush(stdout);
//	}
//	else if(read_size == -1)
//	{
//		perror("recv failed");
//	}
//
//	//Free the socket pointer
//	free(socket_desc);
//
//	return 0;
//}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>

char response[] = "HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html><html><head><title>Bye-bye baby bye-bye</title>"
"<style>body { background-color: #111 }"
"h1 { font-size:4cm; text-align: center; color: black;"
" text-shadow: 0 0 2mm red}</style></head>"
"<body><h1>Goodbye, world!</h1></body></html>\r\n";

int main()
{
	int					one = 1;
	int					client_fd;
	struct sockaddr_in	server_address;
	struct sockaddr_in	client_address;
	socklen_t			socket_in_length = sizeof(client_address);

	// get socket fd
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		err(1, "can't open socket");


	// set socket option	
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));


	// set server port and ip, values, etc
	int port = 8888;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(port);


	// bind socket_fd to addr value
	if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
		close(sock);
		err(1, "Can't bind");
	}


	// make socket_fd listen and can use accept on it
	listen(sock, 5); // the second argument is max_queue_client


	// while loop cause be want our server loop for ever
	while (1) {
		// get client fd, fullfill client_address struct
		client_fd = accept(sock, (struct sockaddr *) &client_address, &socket_in_length);
		printf("got connection\n");

		if (client_fd == -1) {
			perror("Can't accept");
			continue;
		}

		// write on client_fd 
		write(client_fd, response, sizeof(response) - 1); /*-1:'\0'*/
		close(client_fd);
	}
}
