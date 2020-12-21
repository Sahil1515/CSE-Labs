#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/stat.h>


typedef struct data_str
{
    /* data */
    long int msgType;
    char actual_data[100];
}data_str;


int main()
{
    data_str data;

    int s=msgget((key_t)1234,0666|IPC_CREAT);
    if(s==-1)
    {
        perror("msgget");
        exit(1);
    }

    int running=1;

    while (running)
    {
        if(msgrcv(s,(void*)&data,sizeof(data),0,0)==-1)
        {
            perror("msgrcv");
            exit(1);
        }
        printf("Got %s ",data.actual_data);

        if(strncmp(data.actual_data,"end",3)==-1)
        {
            running=0;
        }
    }

    if(msgctl(s,IPC_RMID,0)==-1)
    {
        perror("msgctl");
        exit(1);
    }

    return 1;
    
}