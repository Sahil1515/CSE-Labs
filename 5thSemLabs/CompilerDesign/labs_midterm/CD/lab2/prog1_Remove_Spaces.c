

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>


FILE *fa, *fb;

int main()
{
    fa= fopen("output.c","r");
    fb=fopen("output1.c","w+");

    char ca,cb;

    ca=getc(fa);

    while(ca!=EOF)
    {
        if(ca=='\t' || ca==' ')
        {
            putc(' ',fb);

            while (ca=='\t' || ca==' ')
            {
                ca=getc(fa);
            }
            putc(ca,fb);
        }
        else
        {
            putc(ca,fb);
        }

        ca=getc(fa);
        
    }

    return 0;

}