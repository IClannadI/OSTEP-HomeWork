#define _GNU_SOURCE
#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>

int main()
{
	cpu_set_t set;  // cpu set
	CPU_ZERO(&set);
	CPU_SET(0, &set);  // add first (only one) CPU to cpu set
	if (sched_setaffinity(0, sizeof(cpu_set_t), &set) < 0)  // dedicate parent process to cpu 1
		printf("Error when dedicate a process\n");

	pid_t pid;	
	int fd1[2], fd2[2];
	char buf1[20], buf2[20];
	if (pipe(fd1) < 0 || pipe(fd2) < 0) {  // creating two pairs of pipe
		printf("Error when creating pipe\n");
		exit(1);
	}
	
	write()
	pid = fork();
	if (pid < 0) {
		printf("Error when fork a process\n");
	} else if (pid == 0) {  // child process 
		if (sched_setaffinity(0, sizeof(cpu_set_t), &set) < 0)  // dedicate child process to cpu 1
			printf("Error when dedicate a process\n");
		read(fd1[0], buf1, 10);

	} else {  // parent process

	}
}
