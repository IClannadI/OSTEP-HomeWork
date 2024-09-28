#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	pid_t pid;	
	pid = fork();
	if (pid == 0) {
		char * my_argv[] = {"-a", (char *)NULL};
		if (execv("/bin/ls", my_argv) < 0) {
			printf("Error when exec\n");
			exit(-1);
		}
		exit(0);
			
	}
	wait(NULL);
	printf("Goodbye\n");
	return 0;
}
