
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
	int status;
	pid_t pid;
	pid = fork();

	if (pid == -1)
	{
		printf("CHILD NOT CR3EATED\n");
	}
	else if (pid == 0)
	{

		for (int i = 0; i < 10; i++)
		{
			/* code */
			printf("I AM CHILD\n");
		}

		// exit(0);
	}
	else
	{
		wait(NULL);
		printf("I AM PARENT\n");
		printf("CHILD RETURNED :%d \n", status);
	}
}