
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

FILE *fa, *fb;

int main()
{
    fa = fopen("input1.c", "r");
    fb = fopen("output.c", "w+");

    if(fa==NULL)
    {
        printf("Can't open the file\n");
        exit(1);
    }

    char ca, cb;

    ca = getc(fa);

    while (ca != EOF)
    {
       if(ca=='\n')
       {
           putc(ca,fb);
           while (ca=='\n')
           {
               /* code */
               ca=getc(fa);
           }
           ungetc(ca,fa);
       }
       else
       {
           putc(ca,fb);
       }
       
        ca = getc(fa);
    }

    return 0;
}