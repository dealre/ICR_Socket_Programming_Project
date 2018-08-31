//Socket Programming Example
//Multiple connection Server Side
//By: Robert Deal
//Date: 8/31/2018

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

#define MAX_CLIENTS 100
#define NAME_SIZE 16
#define MSG_SIZE 1024

void error(char *msg) {
	perror(msg);
	exit(0);
}

typedef struct{
	struct sockaddr_in addr;
	char name[16];
	int conn_fd;
	int cli_unique_id;
}client_user;

client_td *clients[MAX_CLIENTS];

void queue_add

void queue_delete

void send_message_general // except the sender

void send_message_all // send to all clients

void send_message_back // only sender

void send_active_list 

void clear_newline

void print_client_ip

void client_handler

void initialize_server() {
	// Variables
	int master_sock, new_socket, client_socket[max_clients];
	struct sockaddr_in address;
	char buffer[1024];
	fd_set readfds;
	
	// Socket
	master_sock ;
	if ((master_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error("ERROR - Socket creation failed");
	}
	if (setsockopt(master_sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
		error("ERROR - Socket creation failed");
	}

	// serv_addr
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	
	// binding
	if (bind(master_sock, (struct sockaddr *) &address, sizeof(address)) < 0 {
		error("ERROR - Binding to port failed");
	}
	
	// listening
	if (listen(master_sock, max_pending_connections) < 0){
		error("ERROR - Listening failed");
	}	
	return;
}

int main(int argc, char *argv[]) {
	
	// initial argument check
	if (argc != 2) { error("ERROR - Requires single port argument"); }
	printf("Setting server up on port: %s\n",argv[1]);
	int port = argv[2];
	
	// manually adjustable variables
	int max_clients = 4;
	int max_pending_connections = 3;
	
	while(1){
		
	}

	return;
}

