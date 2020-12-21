#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>

typedef struct data_str
{
    /* data */
    long int msgType;
    char actual_data[100];
} data_str;

int palindrome(int n)
{
    printf("yeah: %d ", n);

    int originalN = n;
    int last_digit, reversedN = 0;

    while (n != 0)
    {
        last_digit = n % 10;
        reversedN = reversedN * 10 + last_digit;
        n /= 10;
    }

    printf("REVERSE %d ", reversedN);

    if (originalN == reversedN)
        return 1;

    return 0;
}

int main()
{
    data_str data;

    int s = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (s == -1)
    {
        perror("msgget");
        exit(1);
    }

    int running = 1;

    while (running)
    {
        if (msgrcv(s, (void *)&data, sizeof(data), 0, 0) == -1)
        {
            perror("msgrcv");
            exit(1);
        }
        printf("Got %s ", data.actual_data);

        // printf("%d ", atoi(data.actual_data));

        // printf("hi ");

        if (palindrome(atoi(data.actual_data)) == 1)
        {
            printf("hehfds");
            data.msgType = 1;
            // strcpy(data.actual_data, "1");
            if (msgsnd(s, (void *)&data, sizeof(data), 0) == -1)
            {
                perror("msgsnd");
                exit(1);
            }
            // printf("i called");
        }
        else
        {
            data.msgType = 1;
            strcpy(data.actual_data, "0");
            if (msgsnd(s, (void *)&data, sizeof(data), 0) == -1)
            {
                perror("msgsnd");
                exit(1);
            }
        }

        if (strncmp(data.actual_data, "end", 3) == -1)
        {
            running = 0;
        }

        sleep(1);
    }

    if (msgctl(s, IPC_RMID, 0) == -1)
    {
        perror("msgctl");
        exit(1);
    }

    return 1;
}