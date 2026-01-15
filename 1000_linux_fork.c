#include <stdio.h>
#include <unistd.h>

int main (int argc, char ** argv)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		printf("hello from child process pid=%d\n", pid);
	}
	else
	{
		printf("hello from parent process pid=%d\n", pid);
	}

	printf("BYE from process pid=%d\n", getpid());
	printf("FORK() run ONCE returns/executed TWICE\n");
	return 0;
}
