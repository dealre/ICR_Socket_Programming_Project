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
#include <sys/wait.h>

int main(){
	pid_t num = fork();
	
	if (num < 0){
		perror("Fork error");
		exit(-1);
	}

	if (num != 0){ 
		printf("This is the parent %d, its child is %d\n", getpid(), num);
		wait(NULL);
	}

	if (num == 0){ 
		printf("This is the child %d, its parent is %d\n", getpid(), getppid()); 
	}
	
	printf("both\n");
	
	return 0;	
}




































