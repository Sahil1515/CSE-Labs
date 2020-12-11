#include<sys/types.h>
#include<sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
	pid_t pid;
	char * arr[]={"./prog1.out",NULL};
	pid =fork();

	if(pid==-1)
	{
		printf("Child not created\n");
	}
	else if(pid==0)
	{
		printf("I am child going to run the exec\n");
		execvp(arr[0],arr);
		printf("This will not be executed\n");
		exit(0);
	}
	else {
		wait(NULL);
		printf("I am parent\n");
	}


}