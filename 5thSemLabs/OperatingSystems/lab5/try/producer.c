#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>

#define FIFO_NAME "my_fifo"

int main()
{
    int pipe_fd;
    int res;

    if (access(FIFO_NAME, F_OK) == -1)
    {
        res = mkfifo(FIFO_NAME, 0777);
        if (res == -1)
        {
            printf("Cant't create the named pipe\n");
            exit(1);
        }
    }

    printf("HArsha\n");
    int op =open(FIFO_NAME,O_WRONLY|O_CREAT);
    if(op==-1)
    {
        printf("Can't open the file for writing \n");
        exit(1);
    }

    printf("HArsha bandharu\n");


    // printf(" ji");

    int k=0;
    while (k<5)
    {
        k++;
        printf("Enter the data to write\n");
        char buff[100];
        scanf("%s ",buff);

        write(res,buff,sizeof(buff));
        /* code */
    }
    
    return 0;
}