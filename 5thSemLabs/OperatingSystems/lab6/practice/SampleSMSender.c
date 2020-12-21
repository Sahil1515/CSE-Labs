
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <sys/shm.h>


typedef struct Data_str
{
    long int written_by_you;
    char actual_data[100];
}Data_str;

int main()
{
    Data_str *data;
    void * attach =(void*)0;

    int s= shmget((key_t)1234,sizeof(data),0666|IPC_CREAT);
    if(s==-1)
    {
        perror("shmget");
        exit(1);
    }

    attach = shmat(s,0,0);
    if(attach==(void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    data = (Data_str*)attach;

    int running=1;

    data->written_by_you=0;

    while (running)
    {
        while(data->written_by_you==1)
        {
            sleep(1);
            printf("Waiting for client\n");
        }

        char buff[100];
        int k=0;

        printf("Enter the data to send\n");
        while((buff[k++]=getchar())!='\n');
        buff[k]='\0';

        data->written_by_you=1;
        strcpy(data->actual_data,buff);

        if(strncmp(buff,"end",3)==0)
        {
            running=0;
        }
    }
    if(shmctl(s,0,0)==-1)
    {
        perror("shmctl");
        exit(1);
    }
    return 0;
}