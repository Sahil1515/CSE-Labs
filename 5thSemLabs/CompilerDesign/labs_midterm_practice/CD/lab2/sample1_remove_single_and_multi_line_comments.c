

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


FILE * fa, * fb;



int main()
{
    fa= fopen("input.c","r");
    fb=fopen("output.c","w+");
   
    char cb;
    char ca=getc(fa);

    while(ca !=EOF)
    {
        if(ca=='/')
        {
            cb=getc(fa);
            if(cb=='/')
            {
                while(ca!='\n')
                {
                    ca=getc(fa);
                }
            }
            else if(cb=='*')
            {
               do
               {
                    while(ca!='*')
                        ca=getc(fa);
                    ca=getc(fa);
               } while (ca!='/');
               
            }
            else {
                putc(ca,fb);
                putc(cb,fb);
            }
        }
        else
            fputc(ca,fb);
        ca=fgetc(fa);

    }
return 0;

}
