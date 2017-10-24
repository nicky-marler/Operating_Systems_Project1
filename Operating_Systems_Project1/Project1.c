#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FAILURE 0
#define SUCCESS 1
#define CHILD_PROCESSES 8

//This function is to be called when a new process is to be made. It takes in a counter and substracts by one
int make_process(int count) {

	count--; //Counting down by one
	int pid = fork(); //Creating a new process

	//If making a new process fails
	if (pid < 0) {
		perror("for failed");
		exit(FAILURE);
	}
	//The newly parent process waiting on its child to finsih
	else if (pid > 0) {
		/*parent*/
		int status;
		(void)waitpid(pid, &status, 0);
	}
	//Printing the child PID and making a new process if the counter is above 0
	else {
		/*child*/
		printf("Hello PID %ld\n", (long)getpid());
		if (count > 0) {
			make_process(count);
		}
		_exit(SUCCESS);
	}

	return SUCCESS;
}

//The main function that starts the recurssive program
void main(void) {
	make_process(CHILD_PROCESSES);
}

