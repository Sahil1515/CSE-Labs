//sender


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
	int a=0;
	int msgid = msgget((key_t)1234,0666|IPC_CREAT);
	if(msgid==-1)
	{
		fprintf(stderr,"msgget failed!!\n");
		exit(EXIT_FAILURE);
	}
	printf("Enter a number: ");
	scanf("%d",&a);

	if(msgsnd(msgid, &a, sizeof(int),0)==-1)
	{
		printf("msgsnd failed!!!\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

