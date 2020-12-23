// #include <stdio.h>
// #include <pthread.h>

// #define N 30
// #define MAX_THREADS 4

// int prime_arr[N] = {0};

// void *printprime(void *ptr)
// {
//     int j, flag;
//     int i = (int)(long long int)ptr;
//     while (i < N)
//     {
//         // printf("Thread id[%d] checking [%d]\n",pthread_self(),i);
//         flag = 0;
//         for (j = 2; j <= i / 2; j++)
//         {
//             if (i % j == 0)
//             {
//                 flag = 1;
//                 break;
//             }
//         }

//         if (flag == 0 && (i > 1))
//         {
//             prime_arr[i] = 1;
//         }
//         i += MAX_THREADS;
//     }
// }

// int main()
// {
//     pthread_t tid[MAX_THREADS] ;
//     int count = 0;
//     printf("Enter starting and ending\n");
//     int st, en;
//     scanf("%d %d", &st, &en);

//     for (count = 0; count < MAX_THREADS; count++)
//     {
//         // printf("\r\n CREATING THREADS %d",count);
//         pthread_create(&tid[count], NULL, printprime, (void *)count);
//     }
//     printf("\n");
//     for (count = 0; count < MAX_THREADS; count++)
//     {
//         pthread_join(tid[count], NULL);
//     }

//     int c = 0;

//     for (count = st; count < en; count++)
//         if (prime_arr[count] == 1)
//             printf("%d ", count);
//     printf("\n");

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#define MAX_SIZE 256
typedef struct
{
    int m;
    int n;
    int prime_count;
    int primes[MAX_SIZE];
} prime;

void *generate_primes(void *param)
{
    prime *parameter = (prime *)param;
    //generate primes
    for (int i = parameter->m; i <= parameter->n; i++)
    {
        int root = sqrt(i);
        int j;
        for (j = 2; j <= root; j++)
        {
            if (i % j == 0)
                break;
        }
        if (j == root + 1)
        {
            parameter->primes[parameter->prime_count] = i;
            parameter->prime_count += 1;
        }
    }
    return NULL;
}
int main()
{
    prime p;
    printf("Enter lower limit :\n");
    scanf("%d", &(p.m));
    printf("Enter upper limit :\n");
    scanf("%d", &(p.n));
    p.prime_count = 0;
    pthread_t thread1,thread2;
    pthread_create(&thread1, 0, &generate_primes, (void *)&p);
    pthread_create(&thread2, 0, &generate_primes, (void *)&p);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    for (int i = 0; i < p.prime_count; i++)
    {
        printf("%d ", p.primes[i]);
    }
    printf("\n");

    return 0;
}