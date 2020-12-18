#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
	pid_t pid= fork();
	if(pid==-1)
	{
		printf("Child not created\n");
	}
	else if(pid==0)
	{
		printf("Child created\n");
		printf("The child process id from child is:  %d \n", getpid());
		printf("The parent process id from child is:  %d \n", getppid());
		exit(0);
	}
	else {
		wait(NULL);
		printf("I am the parent\n");
		printf("The child process id from parent is:  %d \n", pid);
		printf("The parent process id from parent is:  %d \n", getpid());
	}


}