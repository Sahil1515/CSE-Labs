#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/shm.h>

sem_t mutex, full,empty;
int r,f;
int buff[5];

void prodeuce()
{
    for (int  i = 0; i < 10; i++)
    {
        /* code */

        sem_wait(&empty);
        sem_wait(&mutex);
        printf("produced:item: %d\n",i);
        buff[(++r)%5]=i;
        sleep(1);
        sem_post(&mutex);
        sem_post(&full);
    }
        
}

void consume()
{
    for (int  i = 0; i < 10; i++)
    {
        /* code */

        sem_wait(&full);
        sem_wait(&mutex);
        int item=buff[(++f)%5];
        sleep(1);
        sem_post(&mutex);
        sem_post(&empty);
    }
        
}

int main()
{

    pthread_t thread1,thread2;

    sem_init(&mutex,0,1);
    sem_init(&full,0,1);
    sem_init(&empty,0,5);

    pthread_create(&thread1,0,prodeuce,0);
    pthread_create(&thread2,0,consume,0);

    pthread_join(thread1,0);
    pthread_join(thread2,0);

    return 0;

}