// #include <stdio.h>
// #include <stdlib.h>
// #include <pthread.h>
// #include <errno.h>
// #include <ctype.h>
// #include <unistd.h>

// #define handle_error_en(en, msg) \
// 	do                           \
// 	{                            \
// 		errno = en;              \
// 		perror(msg);             \
// 		exit(EXIT_FAILURE);      \
// 	} while (0)

// volatile int running_threads = 0;
// pthread_t thread[1];
// int numOfElements;
// struct Results
// {
// 	int sum;
// } Results, Results2;
// void *findsum(void *array_ptr)
// {

// 	int i; /*counter*/

// 	int *elements = (int *)array_ptr;
// 	for (i = 0; i < numOfElements; i++)
// 	{
// 		if (elements[i] % 2 == 0)
// 			Results.sum += elements[i];
// 		else
// 			Results2.sum += elements[i];
// 	}

// 	running_threads -= 1;

// 	return NULL;
// }

// int getArrayInput(int n, int *array_ptr)
// {

// 	int input;

// 	int numberOfElements = 0;

// 	printf("Creating Dynamic Array...\n-\n");

// 	for (;;)
// 	{

// 		printf("Enter a positive value:\nNegative Number to Stop\n-\n");

// 		if (scanf("%d", &input) != 1)
// 		{

// 			printf("\nOops that wasn't an Integer\nlets try filling the array again\nRemember INTEGERS only!\n");

// 			exit(EXIT_FAILURE);
// 		}

// 		if (input >= 0)
// 		{

// 			if (numberOfElements == n)
// 			{

// 				n += 1;

// 				array_ptr = realloc(array_ptr, n * sizeof(int));
// 			}

// 			array_ptr[numberOfElements++] = input;
// 		}
// 		else
// 		{

// 			printf("\nNumber of Integers: %d\n", numberOfElements);

// 			break;
// 		}
// 	}

// 	return numberOfElements;
// }

// void createThreads(int *array_ptr)
// {

// 	int s;

// 	s = pthread_create(&thread[2], NULL, findsum, (void *)array_ptr);

// 	if (s != 0)
// 	{

// 		handle_error_en(s, "pthread_create");
// 	}

// 	running_threads += 1;
// }
// int main()
// {
// 	int n = 1;

// 	int *array_ptr = malloc(n * sizeof(int));

// 	numOfElements = getArrayInput(n, array_ptr);

// 	createThreads(array_ptr);

// 	while (running_threads > 0)
// 	{

// 		sleep(1);
// 	}
// 	printf("\nThe sum of even %d and odd %d\n", Results.sum, Results2.sum);
// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *
sum_odd(void *a)
{
	int *arr = (int *)a;
	int n = arr[0];
	int sum = 0;
	for (int i = 1; i < n + 1; i++)
	{
		if (arr[i] % 2 != 0)
			sum += arr[i];
	}
	return ((void *)sum);
}
void *sum_even(void *a)
{
	int *arr = (int *)a;
	int n = arr[0];
	int sum = 0;
	for (int i = 1; i < n + 1; i++)
	{
		if (arr[i] % 2 == 0)
			sum += arr[i];
	}
	return ((void *)sum);
}
int main()
{
	int n;
	printf("Enter the number of numbers:\n");
	scanf("%d", &n);
	int *arr = (int *)malloc(sizeof(int) * (n + 1));
	arr[0] = n;
	printf("Enter the number:\n");
	for (int i = 1; i < n + 1; i++)
		scanf("%d", &arr[i]);
	int ans1 = 0, ans2 = 0;
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, &sum_odd, (void *)arr);
	pthread_join(thread1, (void **)&ans1);
	pthread_create(&thread2, NULL, &sum_even, (void *)arr);
	pthread_join(thread2, (void **)&ans2);

	printf("Sum of odd numbers in array is %d\n", ans1);
	printf("Sum of even numbers in array is %d\n", ans2);
	return 0;
}