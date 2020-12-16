#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nextToken.h"

token t;
FILE *fa, *fb, *file;

void Program();
void declarations();
void data_type();
void identifier_list();
void assign_stat();


void Program()
{
    if(strcmp(t.token_name,"main")==0)
    {
        t=getNextToken(fa);
        if(strcmp(t.token_name,"(")==0)
        {
            t=getNextToken(fa);
            if(strcmp(t.token_name,")")==0)
            {
                t=getNextToken(fa);
                if(strcmp(t.token_name,"{")==0)
                {
                    t = getNextToken(fa);
                    declarations();
                    assign_stat();
                    
                    t=getNextToken(fa);
                    if(strcmp(t.token_name,"}")==0)
                    return;
                    else {
                        printf("Error at } ( %d %d )",t.row,t.col);
                        exit(0);
                    }
                }
                else printf("Error at  { ( %d %d )",t.row,t.col);

            }
            else {
                        printf("Error at ) ( %d %d )",t.row,t.col);
                        exit(0);
                    }
        }
        else {
                        printf("Error at ( ( %d %d )",t.row,t.col);
                        exit(0);
                    }
    }
    else {
                        printf("Error at main ( %d %d )",t.row,t.col);
                        exit(0);
                    }
}

void declarations()
{
    data_type();
    identifier_list();

    t=getNextToken(fa);
    if(strcmp(t.token_name,";")==0)
    {
        declarations();
    }
}

void data_type()
{
    t=getNextToken(fa);
    if(strcmp(t.token_name,"int")==0 || strcmp(t.token_name,"char")==0 )
    return;
    else printf("Error at ( %d %d )",t.row,t.col);
}

void identifier_list()
{
    t=getNextToken(fa);
     if(strcmp(t.token_name,"id")==0)
     {
         printf("What are you doing\n");
        t=getNextToken(fa);
        if(strcmp(t.token_name,",")==0)
        {
            identifier_list();
        }
    }
    else printf(" Are you mad Error at ( %d %d )",t.row,t.col);

}

void assign_stat()
{
      t=getNextToken(fa);
     if(strcmp(t.token_name,"id")==0)
     {
           t=getNextToken(fa);
            if(strcmp(t.token_name,"=")==0)
            {
                t=getNextToken(fa);
                if(strcmp(t.token_name,"id")==0)
                {
                    t=getNextToken(fa);
                    if(strcmp(t.token_name,";")==0)
                    {
                        return;
                    }
                }
                else  if(strcmp(t.token_name,"num")==0)
                {
                    t=getNextToken(fa);
                    if(strcmp(t.token_name,";")==0)
                    {
                        return;
                    }
                }
            }
            else printf("Error at ( %d %d )",t.row,t.col);
     }
    else printf("Error at ( %d %d )",t.row,t.col);
     
}


void preprocessing()
{
    char ca,cb;
    ca = getc(fa);

    while (ca != EOF)

    {
        if (ca == ' ' || ca == '\t')
        {
            putc(' ', fb);
            while (ca == ' ' || ca == '\t')
                ca = getc(fa);
            ungetc(ca, fa);
        }
        else if (ca == '/')
        {
            cb = getc(fa);
            if (cb == '/')
            {
                while (ca != '\n')
                    ca = getc(fa);
            }
            else if (cb == '*')
            {
                do
                {
                    while (ca != '*')
                        ca = getc(fa);
                    ca = getc(fa);
                } while (ca != '/');
                ca = getc(fa);
            }
            else
            {
                putc(ca, fb);
                putc(cb, fb);
            }
        }
        else if (ca == '#')
        {
            while (ca != '\n')
            {
                ca = getc(fa);
            }
        }
        else
            putc(ca, fb);

        ca = getc(fa);
    }
}

int main()
{
    int prev, ca, cb;
    fa = fopen("input.c", "r");

    if (fa == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    fb = fopen("output.c", "w+");

    preprocessing();
    
    fclose(fa);
    fclose(fb);

    file = fopen("output.c", "r");

    t = getNextToken(file);
    printf("%s ",t.token_name);

    Program();
}