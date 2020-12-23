// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <unistd.h>
// #include <sys/ipc.h>
// #include <sys/msg.h>

// typedef struct data_str
// {
//     /* data */
//     long int msgType;
//     char actual_msg[100];
// } data_str;

// int main()
// {
//     data_str data;

//     int s = msgget((key_t)1234, 0666 | IPC_CREAT);
//     if (s == -1)
//     {
//         perror("msgget");
//         exit(1);
//     }

//     int running = 1;

//     while (running)
//     {
//         /* code */
//         char buff[100];
//         printf("Enter the data to send\n");
//         scanf("%s", buff);

//         data.msgType = 1;
//         strcpy(data.actual_msg, buff);

//         if(msgsnd(s,buff,sizeof(buff),0)==-1)
//         {
//             perror("msgsnd");
//             exit(1);
//         }

//         if(msgrcv(s,buff,sizeof(buff),0,0)==-1)
//         {
//             perror("msgrcv");
//             exit(1);
//         }





//     }
// }




















#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct data_str
{
    /* data */
    int mgs_written_by_you;
    char actual_data[100];
}data_str;


int main()
{
    data_str *data;

    void * attach =(void*)0;

    int s=shmget((key_t)1234,sizeof(data),0666|IPC_CREAT);

    if(s==-1)
    {
        perror("shmget");
        exit(1);
    }

    attach=shmat(s,0,0);
    if(attach==(void*)-1)
    {
        perror("shmat");
        exit(1);
    }

    data=(data_str*)attach;

    data->mgs_written_by_you=0;







}
















