// C program to illustrate
// write system Call
#include <stdio.h>
#include <fcntl.h>
#include<string.h>
#include<unistd.h>


int main()
{
    int sz;


    printf("\n\n");

    sz = write(5, "hello geeks\n", strlen("hello geeks\n"));

    printf("called write( , \"hello geeks\\n\", %ld)."
           " It returned %d\n",
           strlen("hello geeks\n"), sz);
}
