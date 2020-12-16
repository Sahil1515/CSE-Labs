
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
        char buffer[4096];
        memset(buffer, '\0', sizeof(buffer));
        printf("Child reading\n");

        // Reading from the pipe
        int r= read( arr[0] , buffer, sizeof(buffer));
        FILE * fw= fopen("pro3_bin2.bin", "wb+");
        int w= fwrite(buffer,sizeof(buffer),100,fw);
        for (int i = 0; i < 100; i++)
        {
            printf("%c ", buffer[i]);
        }
        close(arr[0]);
        return 0; 
    }
    else
    {
        printf("Parent process\n");
        close(arr[0]);
        char buffer[4096];
        memset(buffer, '\0', sizeof(buffer));
        FILE *f1=fopen("pro3_bin.bin","rb");
        int r = fread(buffer,sizeof(buffer),100,f1);
        
        // Writing to the pipe
        int w=write(arr[1], buffer, sizeof(buffer));
        close(arr[0]);
        wait(NULL);
    }

    printf("\nExiting the program\n");
    return 0;
    
    
}