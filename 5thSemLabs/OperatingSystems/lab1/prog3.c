
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>


int main()
{
	unsigned int a=342;
	int b=3453;
	char c='c';
	char * d ="HI i am sahil";
	float e= 2.3;
	double f= 3.4323;
	errno= EPERM;

	printf("Unsigned int %u\n",a);
	printf("Integer %d\n",b);
	printf("character %c\n",c);
	printf("String %s\n",d);
	printf("Float %f\n",e);
	printf("Double  %f\n",f);
	printf("Error Number : %m\n");

	return 0;

}