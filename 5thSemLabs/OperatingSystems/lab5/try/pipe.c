#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{

    int fd[2];
    int p = pipe(fd);

    if (p == -1)
    {
        printf("Can't make the pipe\n");
        exit(1);
    }

    int f = fork();

    if (f == -1)
    {
        printf("Can't make the child process\n");
        exit(1);
    }
    else if (f == 0)
    {
        /* code */
        close(fd[1]);

        // while (1)
        // {
            /* code */
            char buff[100];

            int r = read(fd[0], buff, sizeof(buff));
            if (r == -1)
            {
                printf("Can;t read\n");
                exit(1);
            }

            buff[r] = '\0';
            printf("Data read is :");
            puts(buff);

            close(fd[0]);
        // }
    }
    else
    {
        close(fd[0]);
        char buff[100];
        // while(1)
        // {
            printf("Enter the data to send from parent:\n");
            scanf("%s", buff);

            int w = write(fd[1], buff, sizeof(buff));
        // }
    }
}