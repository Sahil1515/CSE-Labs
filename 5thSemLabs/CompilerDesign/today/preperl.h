#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
void removeDirectives()
{
    FILE *fr,*fw;
    char c;
    fr=fopen("output.c","r");
    fw=fopen("input.c","w");
    c=getc(fr);
    while(c!=EOF)
    {
        if(c=='#')
            while(c!='\n')
                c=getc(fr);
        else
            putc(c,fw);
        c=getc(fr);
    }
    fclose(fr);
    fclose(fw);
}
void removeSpaces()
{
    FILE *fr,*fw;
    char c;
    fr=fopen("input.c","r");
    fw=fopen("output.c","w");
    c=getc(fr);
    while(c!=EOF)
    {
        if(c==' ' || c=='\t')
        {
            putc(' ',fw);
            c=getc(fr);
            if(c==' ' || c=='\t')
                while(c==' ' || c=='\t')
                    c=getc(fr);
            putc(c,fw);

        }
        else
        {
            putc(c,fw);
        }
        c=getc(fr);
    }
    fclose(fr);
    fclose(fw);
}
void preprocess()
{
    FILE *fr,*fw;
    /*fr=fopen("input.c","r");
    fw=fopen("output.c","w+");
    char c=getc(fr);
    while(c!=EOF)
    {
        if(c=='/')
        {
            c=getc(fr);
            if(c=='/')
            {
                while(c!='\n')
                    c=getc(fr);
            }
            else if(c=='*')
            {
                c=getc(fr);
                while(1)
                {
                    if(c=='*')
                    {
                        c=getc(fr);
                        if(c=='/')
                            break;
                    }
                    c=getc(fr);
                }
            }
            else
            {
                fseek(fr,-1,SEEK_CUR);
                putc(c,fw);
            }
        }
        else
        {
            putc(c,fw);
        }
        c=getc(fr);
    }
    putc(EOF,fw);
    fclose(fr);
    fclose(fw);*/
    removeDirectives();
    removeSpaces();
}