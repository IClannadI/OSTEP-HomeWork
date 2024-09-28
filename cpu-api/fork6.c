#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int flag = 1;
	int fd[2];
	if (pipe(fd) < 0) {
		printf("Create pipe error\n");
		exit(1);
	}

	pid_t pid1, pid2;
	pid1 = fork();
	if (pid1 == 0) {  // child process 1
		printf("Child process %d is created\n", getpid());
		close(fd[0]);
		dup2(fd[1], STDIN_FILENO);
		printf("Hello, world\n");
		close(fd[1]);
		exit(0);
	} else {
		wait(NULL);
		pid2 = fork();
		if (pid2 == 0) {  // child process 2
			printf("Child process %d is created\n", getpid());
	 		close(fd[1]);
			dup2(fd[0], STDOUT_FILENO);
			close(fd[0]);
			exit(0);
		} else {  // parent process
			wait(NULL);
			exit(0);
		}
	} 	
} 
