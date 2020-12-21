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
        perror("msgget\n");
        exit(1);
    }

    int running=1;

    while (running)
    {
        char buff[100];
        int k=0;

        printf("Enter the data to send\n\n");
        // while((buff[k++]=getchar())!='\n');
        // buff[k]='\0';

        fgets(buff,sizeof(buff),stdin);
        puts(buff);
        // printf("hi\n");

        data.msgType=1;
        strcpy(data.actual_data,buff);

        if(msgsnd(s,(void*)&data,sizeof(data),0)==-1)
        {
            perror("msgsnd\n");
            exit(1);
        }

        // sleep(3);
        if (msgrcv(s,(void*)&data,sizeof(data),0,0)==-1)
        {
            perror("msgrcv\n");
            exit(1);
            /* code */
        }

        if(strcmp(data.actual_data,"1")==0)
        {
            printf("Palindrome\n\n");
            // printf("%s ",data.actual_data);

        }
        else
        {
            /* code */
            printf("Not Palindrome\n\n");
            printf("%s ",data.actual_data);
        }

        if(strncmp(buff,"end",3)==0)
        {
            running=0;
        }
    }
    if(msgctl(s,IPC_RMID,0)==-1)
    {
        printf("msgctl\n");
        exit(1);
    }
    return 0;

}
