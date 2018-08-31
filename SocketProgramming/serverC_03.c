//Socket Programming Example
//Server Side
//By: Robert Deal
//Date: 8/27/2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <netdb.h>
	
void error(const char *msg) {
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[]) {
	
	// initial argument check
	if (argc < 2) { error("ERROR - Missing argument for port"); }
	if (argc > 2) { error("ERROR - Too many arguments for port"); }
	printf("Setting server up on port: %s\n",argv[1]);
	
	// initial variables
	int sockfd, newsockfd, portnum, n;
	int i = 1;
	char buffer [256];
	bool quit = false;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;
	
	// socket creation
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) { error("ERROR - Socket creation failed"); }
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portnum = atoi(argv[1]);
	
	// setting up the serv_addr struct
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portnum);
	
	// isaac the _______
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){ error("ERROR - Binding to port failed");}

	// listen for connections
	listen(sockfd, 4);
	clilen = sizeof(cli_addr);
	
	// accept connection
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);	
	if (newsockfd < 0) { error("ERROR - Accepting connection failed"); }
		
	// start of the fork	
	char child_buffer[256];
	pid_t forknum = fork();	
	if(forknum < 0){ error("ERROR - Fork creation failed"); }
	
	if(forknum != 0){ // parent
		printf("parent here\n"); /////////////////////////////remove later	
		while(1){
			bzero(buffer, 256);

			n = read(newsockfd, buffer, 256);
			if(n < 0){ error("ERROR - Reading data failed"); }

			printf("Client: %s\n", buffer);
			bzero(buffer, 256);	
		}
	}
	
	if(forknum == 0){ // child
		printf("child here\n"); ////////////////////////remove later
		while(1){
			bzero(child_buffer, 256);
			printf("Server: ");
			fgets(child_buffer, 256, stdin);

			n = write(newsockfd, child_buffer, 256);
			if(n < 0){ error("ERROR - Writing data failed"); }

			bzero(child_buffer, 256);
		}
	}	

	close(newsockfd);
	close(sockfd);
	
	return 0;
	exit(1);
}













