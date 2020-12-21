#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>



typedef struct data_str
{
    long int msgType;
    char actual_data[100];
}data_str;

int main()
{
    data_str data;

    int s = msgget((key_t)1234,0666|IPC_CREAT);
    if(s==-1)
    {
        perror("msgget");
        exit(1);
    }

    int running=1;

    while (running)
    {
        char buff[100];
        int k=0;

        printf("Enter the data to send\n");
        while((buff[k++]=getchar())!='\n');
        buff[k]='\0';

        // printf("hi");

        data.msgType=1;
        strcpy(data.actual_data,buff);

        if(msgsnd(s,(void*)&data,sizeof(data),0)==-1)
        {
            perror("msgsnd");
            exit(1);
        }

        if(strncmp(buff,"end",3)==0)
        {
            running=0;
        }
    }
    if(msgctl(s,IPC_RMID,0)==-1)
    {
        printf("msgctl");
        exit(1);
    }
    return 0;

}
