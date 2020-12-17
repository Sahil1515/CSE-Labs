#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<error.h>
#include<sys/wait.h>

int main()
{
    int arr[2];

    // Creating the pipe
    int fd=pipe(arr);

    if(fd ==-1)
    {
        printf("Can't create a pipe\n");
        exit(1);
    }
    int f=fork();

    if(f==-1)
    {
        printf("Can't create a child process\n");
        exit(2);
    }
    else if (f==0)
    {
        printf("Child process\n");
        close(arr[1]);
        int buffer;
        printf("Child reading\n");

        // Reading from the pipe
        int r= read( arr[0] , &buffer, sizeof(buffer));
        buffer=buffer*10;
        printf("Buffer after multiplication by 10 :%d \n",buffer);
        close(arr[0]);
    }
    else
    {
        printf("Parent process\n");
        close(arr[0]);
        int buffer=30;
        printf("Parent writing %d \n", buffer);
        
        // Writing to the pipe
        int w=write(arr[1], &buffer, sizeof(buffer));
        close(arr[0]);
        wait(NULL);
    }

    printf("Exiting the program\n");
    return 0;
    
    
}