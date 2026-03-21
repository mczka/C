#include <stdio.h>
#include <unistd.h>

int main (int argc, char ** argv)
{
        pid_t pid = fork();
        if (pid != 0)
        {
                printf("hello from child process pid=%d\n", pid);
                static char *_argv[] = {"date", "+%s", NULL};
                static char *_envp[] = {NULL};

                execve("/bin/date", _argv, _envp);

        }
        else
        {
                printf("hello from parent process pid=%d\n", pid);
        }

        printf("BYE from process pid=%d\n", getpid());

        return 0;
}
