#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        printf("Fork failed\n");
        exit(0);
    }
    else if (pid == 0)
    {
        printf("In Child:\n");
        for (int i = 0; i < 10; i++)
        {
            printf("Child process - %d\n", i + 1);
        }
        printf("Parent PID : %d\nChild PID : %d\n", getppid(), getpid());
        exit(0);
    }
    else
    {
        printf("In Parent:\n");
        for (int i = 0; i < 2; i++)
            printf("Parent process - %d\n", i + 1);
        sleep(10);
        int p = fork();
        if (p == 0)
        {
            printf("In child\n");
            sleep(1);
            printf("Parent pid : %d\n", getppid());
        }
        else
        {
            printf("Exiting parent\n");
            exit(0);
        }
        return 0;
    }
}