#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int fd[2];  // file descriptions

	if (pipe(fd) == -1) {
		printf("Error when opening the pipe\n");
	}

	pid_t pid = fork();

	if (pid == 0) {
		int flag = 0;
		close(fd[0]);  // fd[0] is used to read to the pipe
		printf("hello, ");
		flag = 1;
		write(fd[1], &flag, sizeof(int));
		close(fd[1]);
		exit(0);
	} else {
		int flag = 0;
		close(fd[1]);
		read(fd[0], &flag, sizeof(int));
		while (1) {
			if (flag == 0)
				continue;
			else {
				printf("world\n");
				break;
			}
		}
		close(fd[0]);
	}
	exit(0);
}
