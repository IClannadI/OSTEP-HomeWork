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
	if (pipe(fd1) < 0 || pipe(fd2) < 0) {  // creating two pairs of pipe
		printf("Error when creating pipe\n");
		exit(1);
	}

	struct timeval start, end;
	int N = 10000;

	if (sched_setaffinity(0, sizeof(cpu_set_t), &set) < 0) { // bind parent process to cpu 1
		printf("Error when dedicate a process\n");
		exit(1);
	}

	pid = fork();
	if (pid < 0) {
		printf("Error when fork a process\n");
	} else if (pid == 0) {  // child process 
		char buf = '0';  // each process has own buf to avoid data confliction
		close(fd1[1]);
		close(fd2[0]);
		for (int i = 0; i < N; ++i) {
			read(fd1[0], &buf, 1);
			write(fd2[1], &buf, 1);
		}
		close(fd1[0]);
		close(fd2[1]);
	} else {  // parent process
		char buf = '0';
		close(fd1[0]);
		close(fd2[1]);
		gettimeofday(&start, NULL);
		for (int i = 0; i < N; ++i) {
			write(fd1[1], &buf, 1);
			read(fd2[0], &buf, 1);
		}
		gettimeofday(&end, NULL);
		printf("context switch: %f microseconds\n", (float)(end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / N / 2);
		wait(NULL);
		close(fd1[1]);
		close(fd2[0]);
		exit(0);
	}
}
