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

#define MAX_CLIENTS 4
#define MSG_SIZE 256

static unsigned int client_count = 0;
static int user_id = 0;

void error(char *msg) {
	perror(msg);
	exit(0);
}

typedef struct{
	struct sockaddr_in addr;
	int new_sock;
	int user_id;
	int online;
}client_user;

client_user clients[MAX_CLIENTS];

void queue_add(client_user *cl){
	int i;
	for(i=0;i<MAX_CLIENTS;i++){
		if(clients[i].online != 1){
			clients[i] = *cl;
			return;
		}
	}
}

void queue_delete(int user_id){
	int i;
	for(i=0;i<MAX_CLIENTS;i++){
		if(clients[i].online == 1){
			if(clients[i].user_id == user_id){
				clients[i].online = 0;
				return;
			}
		}
	}
}

void send_message(char *s, int user_id){
	int i;
	for(i=0;i<MAX_CLIENTS;i++){
		if(clients[i].online == 1){
			if(clients[i].user_id != user_id){
				write(clients[i].new_sock, s, strlen(s));
			}
		}
	}
}

void send_message_all(char *s){
	int i;
	for(i=0;i<MAX_CLIENTS;i++){
		if(clients[i].online == 1){
			write(clients[i].new_sock, s, strlen(s));
		}
	}
}

void *client_handler(void *arg){
	char buffer_output[MSG_SIZE];
	char buffer_input[MSG_SIZE];
	int reader;
	
	client_count++;
	client_user *client = (client_user *)arg;
	printf("Accepted User: %i\n",client->user_id);
	sprintf(buffer_output,"Accepted User: %i\n",client->user_id);
	send_message_all(buffer_output);
	
	while((reader = read(client->new_sock, buffer_input, sizeof(buffer_input)-1)) > 0){
		buffer_input[reader] = '\0';
		buffer_output[0] = '\0';
		
		printf("%i: %s\n",client->user_id, buffer_input);
		sprintf(buffer_output,"%i: %s",client->user_id, buffer_input);
		send_message(buffer_output, client->user_id);
	}
	close(client->new_sock);		
	queue_delete(client->user_id);

	printf("User Left: %d\n", client->user_id);
	sprintf(buffer_output,"User Left: %i\n",client->user_id);
	send_message_all(buffer_output);
	client->online = 0;

	free(client);
	client_count--;
	pthread_detach(pthread_self());
	return 0;
}
		
int main(int argc, char *argv[]) {
	
	// initial argument check
	if (argc != 2) { error("ERROR - Requires single port argument"); }
	printf("Setting server up on port: %s\n",argv[1]);
	
	// manually adjustable variables
	int max_clients = 4;
	int max_pending_connections = 4;
	
	// Variables
	int master_sock = 0;
	int new_sock = 0;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	pthread_t tid;
	int port = atoi(argv[1]);
	
	// Socket
	if ((master_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		error("ERROR - Socket creation failed");
	}

	// serv_addr
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(port);
	
	// binding
	if (bind(master_sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0 ){
		error("ERROR - Binding to port failed");
	}

	// listening
	if (listen(master_sock, max_pending_connections) < 0){
		error("ERROR - Listening failed");
	}
	printf("Server Started on port: %s\n", argv[1]);

	while(1){
		socklen_t clilen = sizeof(client_address);
		new_sock = accept(master_sock, (struct sockaddr*)&client_address, &clilen);
		if (new_sock < 0) {
			error("ERROR - Accepting connection failed");
		}
		
		if ((client_count + 1) == MAX_CLIENTS){
			printf("Maximum clients reached, rejecting attempt\n");
			close(new_sock);
			continue;
		}
		
		client_user *client = (client_user *)malloc(sizeof(client_user));
		client->addr = client_address;
		client->new_sock = new_sock;
		client->user_id = user_id++;
		client->online = 1;
		printf("New connection: %d \n",client->user_id);
		
		queue_add(client);
		pthread_create(&tid, NULL, &client_handler, (void*)client);
		
	}
	return 0;
}
