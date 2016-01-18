#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>

int main()
{
	int pipefd[2];
	pid_t pid;

	if (pipe(pipefd)==-1)
	{
		printf("pipe failed!\n");
		exit(1);
	}

	pid=fork();
	if (pid==-1) //failed
	{
		printf("fork failed!\n");
		exit(1);
	} else
	if (pid==0) //child process
	{
		char message[110];
		close(pipefd[1]);
		read(pipefd[0],message,100);
		printf("Child process:read from pipe is--%s\n",message);
	} else
	if (pid>0) //parent process
	{
		char message[110];
		scanf("%s",message);
		close(pipefd[0]);
		write(pipefd[1],message,strlen(message)+1);
	}
	return 0;
}
