#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main()
{
    pid_t p=fork();
    if(p==-1)
    {
        printf("Can't crete the process\n");
        exit(1);
    }
    else if(p==0)
    {
        printf("Child process\n");
        printf("%d pid \n",getppid());
        sleep(3);
        printf("%d pid \n",getppid());
    }
    else
    {
        sleep(2);
        printf("Parent\n");
    }
    
return 0;

}