/*
Socket Programming Example
Server Side
By: Robert Deal
Date: 8/27/2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main() {
	// maximum number of possible connections
	int backlog = 10;
	// port that the socket will listen for
	string port = "12345"

	// socket file descriptor
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	// 0 if success, -1 if fail ??
	struct sockaddr {
		sa_family_t sa_family; // right?
		char sa_data[14];
	};

	// activates/initializes or whatever the socket descriptor
	int bind(sock_fd, const struct sockaddr *addr, socklen_t addrlen)

	// gets the socket to start listening for stuff
	int listen(int sock_fd, int backlog)

	// gets the server to accept an incoming comunication
	newsockfd = accept(sockfd, (struct sockaddr*)&addr, &addrlen);

	// asks a server to connect to it
	int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);


	//////////////////////////////////////////////////
	// after the connection is established
	//////////////////////////////////////////////////

	// checks the connection for a message
	int read(newsockfd, buffer, buffer_size); //buffer is a string and

	// sends a message through the connection
	int write(newsockfd, buffer, buffer_size); //buffer_size is the size of string

	// send() and receive() exist but require another argument

	// closes the connection between the client/server
	close()
	
	//////////////////////////////////////////////////
	// now connection is over
	//////////////////////////////////////////////////






	return 0;
}

