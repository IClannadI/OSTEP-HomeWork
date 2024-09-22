#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
	pid_t pid;
	int x = 1;

	pid = fork();
	if (pid == 0) {  // child process
		x += 1;
		printf("x in child process is: %d\n", x);
		exit(0);
	}

	printf("x in parent process is: %d\n", x);
	exit(0);
}
