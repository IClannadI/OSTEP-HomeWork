#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	FILE* fp = NULL;
	
	fp = fopen("test.txt", "a+");
	if (fp == NULL) {
		printf("File can't open :(\n");
		exit(0);
	}

	printf("The parent process is %d\n", getpid());

	pid = fork();
	size_t size = fprintf(fp, "Hello world by %d\n", getpid());
	if (size < 0) {
		printf("fail to access the file by %d\n", getpid());
	}

	if (fp != NULL)
		fclose(fp);	

	if (pid == 0)
		exit(0);
	else {
		waitpid(-1, NULL, 0);
		exit(0);
	}
}
