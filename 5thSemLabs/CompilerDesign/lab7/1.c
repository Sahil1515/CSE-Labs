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
void id_listPrime();
void assign_statPrime();

void Program()
{
    if (strcmp(t.token_name, "main") == 0)
    {
        t = getNextToken();
        if (strcmp(t.token_name, "(") == 0)
        {
            t = getNextToken();
            if (strcmp(t.token_name, ")") == 0)
            {
                t = getNextToken(fa);
                if (strcmp(t.token_name, "{") == 0)
                {
                    
                    declarations();
                    assign_stat();

                    t = getNextToken(fa);
                    if (strcmp(t.token_name, "}") == 0)
                        return;
                    else
                    {
                        printf("Error at program1 ( %d %d )\n", t.row, t.col);
                        // printf("%s\n",t.token_name);
                        exit(0);
                    }
                }
                else
                {
                    printf("Error at  program2 { ( %d %d )\n", t.row, t.col);
                    exit(1);
                }
            }
            else
            {
                printf("Error at program )3 ( %d %d )\n", t.row, t.col);
                exit(0);
            }
        }
        else
        {
            printf("Error at program4 ( ( %d %d )\n", t.row, t.col);
            exit(0);
        }
    }
    else
    {
        printf("Error at program5 ( %d %d )\n", t.row, t.col);
        exit(0);
    }
}

void declarations()
{

    t = getNextToken();
    char first[2][20] = {"int", "char"};

    int flag = 0;
    for (int i = 0; i < 2; i++)
    {
        /* code */
        if (strcmp(t.token_name, first[i]) == 0)
            flag = 1;
    }

    if (flag)
    {
        data_type();
        identifier_list();

        if (strcmp(t.token_name, ";") == 0)
        {
            declarations();
        }
        else
        {
            printf("No ; %d %d\n", t.row, t.col); // Error
            exit(1);
        }
    }
}

void data_type()
{
    if (strcmp(t.token_name, "int") == 0 || strcmp(t.token_name, "char") == 0)
        return;
    else
    {
        printf("Error datatype\n");
        exit(1);
    }
}

void identifier_list()
{
    t = getNextToken(fa);
    if (strcmp(t.token_name, "id") == 0)
    {
        id_listPrime();
    }
}

void id_listPrime()
{
    t = getNextToken(fa);
    if (strcmp(t.token_name, ",") == 0)
    {
        identifier_list();
    }
}

void assign_stat()
{
    if (strcmp(t.token_name, "id") == 0)
    {
        t = getNextToken(fa);
        if (strcmp(t.token_name, "=") == 0)
        {
            assign_statPrime();
        }
        else
        {
            printf("Error at assignment1( %d %d )\n", t.row, t.col);
            exit(1);
        }
    }
}

void assign_statPrime()
{
    t = getNextToken(fa);
    if (strcmp(t.token_name, "id"))
    {
        t = getNextToken();
        if (strcmp(t.token_name, ";")==0)
        {
            return;
        }
        else
        {
            printf("Error is 1;\n");
            exit(1);
        }
    }
    else if (strcmp(t.token_name, "num"))
    {
        /* code */
        t = getNextToken();
        if (strcmp(t.token_name, ";"))
        {
            printf("%s ", t.token_name);
            return;
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