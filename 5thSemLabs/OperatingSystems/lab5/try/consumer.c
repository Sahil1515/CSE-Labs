#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>

#define MY_FIFO "my_fifo"

int main()
{
    int res;

    if(access(MY_FIFO,F_OK)==-1)
    {
        res=mkfifo(MY_FIFO,0777);
        if(res==-1)
        {
            printf("Can't create the named pipe\n");
            exit(1);
        }
    }

    int op=open(MY_FIFO,O_WRONLY);
    if(op==-1)
    {
        printf("Can't open the pipe\n");
        exit(1);
    }

    int k=5;
    while (k--)
    {
        /* code */
        char buff[100];
        read(op,buff,sizeof(buff));
        puts(buff);

    }
    
    return 0;
}