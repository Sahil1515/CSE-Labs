#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include <sys/shm.h>


typedef struct Data_str
{
    long int written_by_you;
    char actual_data[100];
}Data_str;


int main()
{
    void * attach;
    Data_str *data;

    int s=shmget((key_t)1234,sizeof(data),0666|IPC_CREAT);
    if(s==-1)
    {
        perror("shmget");
        exit(1);
    }

    attach = shmat(s,0,0);
    if(attach==(void*)-1)
    {
        perror("shmat");
        exit(1);
    }

    data = (Data_str*)attach;

    int running=1;

    while (running)
    {
        /* code */
        if (data->written_by_you)
        {
            printf("shared memory has:\n");
            puts(data->actual_data);
            data->written_by_you=0;
            sleep(5);
        }
        if(strncmp(data->actual_data,"end",3)==-0)
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