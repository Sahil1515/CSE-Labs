

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>


FILE * fa, * fb;

int main()
{
    fa=fopen("output1.c","r");
    fb=fopen("output2.c","w+");

    char ca,cb;

    ca=getc(fa);

    char directives[11][20]={
        "#include","#define" ,"#undef", "#ifdef", "#ifndef", "#if",
        "#else" , "#elif", "#endif", "#error", "#pragma"
    };

    while (ca!=EOF)
    {
        char buffer[100];
        int i=0;
        int flag=0;

        if(ca=='#')
        {
            while (ca!='\n')
            {
                buffer[i++]=ca;
                ca=getc(fa);
            }
            buffer[i]='\0';

            for (int j = 0; j < 11; j++)
            {
                /* code */
                if(strstr(buffer,directives[j])!=NULL)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==0)
                fputs(buffer,fb);
        }
        else
        {
            putc(ca,fb);
        }
        ca=getc(fa);
    }

    return 0;
    
}