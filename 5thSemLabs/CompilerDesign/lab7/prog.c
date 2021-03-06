#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nextToken.h"

token t;
token s;

FILE *fa, *fb, *file;

void Program();
void declarations();
void data_type();
void identifier_list();
void assign_stat();
void id_listPrime();
void assign_statPrime();

void Program()
{
    if (strcmp(t.token_name, "main") == 0)
    {
        s=t;
        t = getNextToken(fa);
        if (strcmp(t.token_name, "(") == 0)
        {
            s=t;
            t = getNextToken(fa);
            if (strcmp(t.token_name, ")") == 0)
            {
                s=t;
                t = getNextToken(fa);
                if (strcmp(t.token_name, "{") == 0)
                {
                    // t = getNextToken(fa);
                    declarations();
                    assign_stat();
                    
                    s=t;
                    t = getNextToken(fa);
                    if (strcmp(t.token_name, "}") == 0)
                        return;
                    else
                    {
                        printf("Error at program1 ( %d %d )\n", s.row, s.col);
                        // printf("%s\n",t.token_name);
                        exit(0);
                    }
                }
                else
                    {
                        printf("Error at  program2 { ( %d %d )\n", s.row, s.col);
                        exit(1);
                    }
            }
            else
            {
                printf("Error at program )3 ( %d %d )\n", s.row, s.col);
                exit(0);
            }
        }
        else
        {
            printf("Error at program4 ( ( %d %d )\n", s.row, s.col);
            exit(0);
        }
    }
    else
    {
        printf("Error at program5 ( %d %d )\n", s.row, s.col);
        exit(0);
    }
}

void declarations()
{
    s=t;
    t = getNextToken(fa);
    if (strcmp(t.token_name, "int") == 0 || strcmp(t.token_name, "char") == 0)
        identifier_list();

    else
    {
        identifier_list();
        return;
    }

    // t = getNextToken(fa);

    if (strcmp(t.token_name, ";") == 0)
    {
        declarations();
    }
    else
    {
        // printf("%s \n", s.token_name);
        printf("No ; %d %d\n", s.row, s.col); // Error
    }
}

// void data_type()
// {
//     // t = getNextToken(fa);
//     if (strcmp(t.token_name, "int") == 0 || strcmp(t.token_name, "char") == 0)
//         return;
//         else
//         {
//             assign_stat();
//         }

//     // else
//         // printf("Error at datatype ( %d %d )\n", t.row, t.col);
// }

void identifier_list()
{
    s=t;
    t = getNextToken(fa);
    if (strcmp(t.token_name, "id") == 0)
    {
        id_listPrime();
    }
}

void id_listPrime()
{
    s=t;
    t = getNextToken(fa);
    if (strcmp(t.token_name, ",") == 0)
    {
        identifier_list();
    }
}

void assign_stat()
{
    // t = getNextToken(fa);
   
        // t = getNextToken(fa);
        if (strcmp(t.token_name, "=") == 0)
        {
            // printf("yeah");
            // printf("%s ",t.token_name);
            assign_statPrime();
        }
        else
            {
                printf("Error at assignment1( %d %d )\n", s.row, s.col);
                exit(1);
            }
    // }
    // else
    //     printf("Error at assignment ( %d %d ) %s \n", t.row, t.col, t.token_name);
}

void assign_statPrime()
{
    s=t;
    t=getNextToken(fa);
    if (strcmp(t.token_name, "id"))
    {
        s=t;
        t=getNextToken();
        if (strcmp(t.token_name, ";"))
        {
            return ;
        }
        else
        {
            printf("Error is ;");
            exit(1);
        }
        
    }
    else if(strcmp(t.token_name,"num"))
    {
        /* code */
        s=t;
        t=getNextToken();
          if (strcmp(t.token_name, ";"))
        {
            printf("%s ",t.token_name);
            return ;
        }
         else
        {
            printf("Error is ;");
            exit(1);
        }
    }
    else
    {
        printf("Error in assignPrime\n");
    }
}

void preprocessing()
{
    char ca, cb;
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
        printf("Cannot \nopen file \n");
        exit(0);
    }

    fb = fopen("output.c", "w+");

    preprocessing();

    fclose(fa);
    fclose(fb);

    file = fopen("output.c", "r");

    t = getNextToken(file);
    // printf("%s ",t.token_name);

    Program();

    printf("Success\n");
}