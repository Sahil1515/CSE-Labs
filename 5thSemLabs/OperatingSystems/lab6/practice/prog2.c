
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/wait.h>

typedef struct Data_str
{
    long int written_by_you;
    char actual_data;
} Data_str;

int main()
{
    Data_str *data;
    void *attach = (void *)0;

    int s = shmget((key_t)1234, sizeof(data), 0666 | IPC_CREAT);
    if (s == -1)
    {
        perror("shmget");
        exit(1);
    }

    attach = shmat(s, 0, 0);
    if (attach == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }
    data = (Data_str *)attach;

    data->written_by_you = 0;

    int f = fork();
    if (f == -1)
    {
        printf("Can't create the process\n");
        exit(1);
    }
    else if (f == 0)
    {
        printf("Child\n");

        sleep(4);
        if (data->written_by_you == 1)
        {
            data->written_by_you = 2;
            data->actual_data++;
        }
    }
    else
    {
        printf("parent\n");
        char buff;

        if (data->written_by_you != 2)
        {
            printf("Enter the char to send\n");
            scanf("%c", &buff);
            data->actual_data = buff;
            data->written_by_you = 1;
            wait(NULL);
            printf(" parent %c\n", data->actual_data);
        }
    }

    if (shmctl(s, 0, 0) == -1)
    {
        perror("shmctl");
        exit(1);
    }
    return 0;
}