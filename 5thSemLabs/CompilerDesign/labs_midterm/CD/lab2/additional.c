#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/stat.h>


FILE * fa, * fb;


int is_return_type(char buff[])
{
    char keywords[21][20] = {
        "int", "long", "unsigned","double",
        "float","char",  "short",
        "struct"};

    for(int i=0;i<8;i++)
    {
        if(strcmp(keywords[i],buff)==0)
        return 1;
    }

    return 0;
}

int main()
{
    fa=fopen("output2.c","r");
    if(fa==NULL)
    {
        printf("Can't open the file\n");
        exit(1);
    }

    char ca, cb;

    char buff1[100], buff2[100];

    ca=getc(fa);

    while (ca!=EOF)
    {
        int count=0;
        int i=0;

        if(isalpha(ca))
        {
            while (isalpha(ca))
            {
                buff1[i++]=ca;
                ca=getc(fa);
            }
            buff1[i]='\0';

            if(ca=='(')
            {
                
                while (ca!=')')
                {
                    if(ca==',')
                    count++;

                    ca=getc(fa);
                } 

                if(is_return_type(buff2))
                printf("%s %s %d\n\n", buff2,buff1,count+1);
            }
            else
            {
                strcpy(buff2,buff1);
            }
            
        } 

        ca=getc(fa); 
    }

    return 0;
}