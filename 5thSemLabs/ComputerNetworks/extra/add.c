#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
    char a[2];
    char b[2];

    a[0]='4';
    // a[0]='\0';

   

    printf("%d ",atoi(a));

     b[0]='3';
    b[1]='\0';

    printf("%d ",atoi(b));


    // char c[1];
    int c= atoi(a)+atoi(b);

    printf("%d ",c);

    return 0;
}