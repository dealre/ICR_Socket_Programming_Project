//Socket Programming Example
//Client Side
//By: Robert Deal
//Date: 8/27/2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[]) {
	
	// initial argument check
	if (argc < 3) { error("ERROR - Missing argument for port"); }
	if (argc > 3) { error("ERROR - Too many arguments for port"); }
	
	// initial variables
	int sockfd, newsockfd, portnum, n;
	int i = 1;
	char buffer [256];
	struct sockaddr_in serv_addr;
	struct hostent *server;
	portnum = atoi(argv[2]);
	
	// socket creation
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) { error("ERROR - Socket Creation failed"); }

	server = gethostbyname(argv[1]);
	if(server == NULL){ error("ERROR - Host unidentified"); }
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portnum);
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){ error("ERROR - Connection failed"); }
	
	while(1){
		bzero(buffer, 256);
		fgets(buffer, 256, stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if(n < 0){ error("ERROR - Writing data failed"); }
		
		bzero(buffer, 256);
		//n = read(sockfd, buffer, 256);
		//if(n < 0){ error("ERROR - Reading data failed"); }
		
		//printf("Server: %s\n", buffer);
		
		i = strncmp("exit", buffer, 4);
		if(i == 0){ break; }
	}
	
	close(sockfd);
	return 0;
}
