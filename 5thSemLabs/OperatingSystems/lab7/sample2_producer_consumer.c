

#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t mutex, full, empty;

int buff[5],f,r;

void * produce(void * arg)
{
    int i;
    for (int  i = 0; i < 10; i++)
    {
        /* code */
        sem_wait(&empty);
        sem_wait(&mutex);

        printf("Producer item is %d \n",i);
        buff[(++r)%5]=i;
        sleep(5);
        sem_post(&mutex);
        sem_post(&full);
        // printf("full %lu\n",full);
        printf("Hi \n");
    }
    
}

void *consume(void * arg)
{
    int item ,i;

    for (int i = 0; i < 10; i++)
    {
        /* code */
          /* code */
        sem_wait(&full);
        // printf("full %lu\n",full);
        printf("Hello \n");
        sem_wait(&mutex);
        item =buff[(++r)%5]=i;

        printf("Consumed item is %d \n",item);
       
        sleep(5);

        sem_post(&mutex);
        sem_post(&empty);
      

    }
    


}

int main()
{

    pthread_t tid1,tid2;
    sem_init(&mutex,0,1);
    sem_init(&full,0,1);
    sem_init(&empty,0,5);

    pthread_create(&tid1,NULL,produce,NULL);
    pthread_create(&tid2,NULL,consume,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

}