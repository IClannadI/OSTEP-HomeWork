#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	pid_t pid;
	pid = fork();
	
	if (pid == 0) {
		close(1);
		printf("Test from child process\n");
		exit(0);
	}
	int status;
	wait(&status);
	if (WIFEXITED(status)) {
		printf("Child process exit normally\n");
	} else {
		printf("Child process exit badly\n");
	}
	return 0;
}
