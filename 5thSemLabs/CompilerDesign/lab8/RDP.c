#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "la.h"

token t;

void program();
void declarations();
void data_type();
void identifier_list();
void identifier_listPrime();
void statement_list();
void statement();
void assign_stat();
void expn();
void eprime();
void simple_exp();
void seprime();
void term();
void tprime();
void factor();
void decision_stat();
void dprime();
void looping_stat();
void relop();
void addop();
void mulop();

void invalid()
{
    printf("Error at %d %d ", t.row, t.col);
    exit(1);
}

void debug()
{
    printf("%s\n", t.token_name);
}

void program()
{
    if (strcmp(t.token_name, "main") == 0)
    {
        t = getNextToken();
        if (strcmp(t.token_name, "(") == 0)
        {
            t = getNextToken();
            if (strcmp(t.token_name, ")") == 0)
            {
                t = getNextToken();
                if (strcmp(t.token_name, "{") == 0)
                {

                    declarations();
                    statement_list();

                    // t = getNextToken();
                    if (strcmp(t.token_name, "}") == 0)
                    {
                        return;
                    }
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void declarations()
{
    t = getNextToken();

    char dType[2][20] = {"int", "char"};
    int flag = 0;

    for (int i = 0; i < 2; i++)
    {
        /* code */
        if (strcmp(t.token_name, dType[i]) == 0)
        {
            /* code */
            flag = 1;
        }
    }

    if (flag)
    {
        data_type();
        identifier_list();

        // t = getNextToken();
        if (strcmp(t.token_name, ";") == 0)
        {
            declarations();
        }
    }
}

void data_type()
{
    if (strcmp(t.token_name, "int") == 0 || strcmp(t.token_name, "char") == 0)
    {
        return;
    }
    else
    {
        invalid();
    }
}

void identifier_list()
{
    t = getNextToken();
    if (strcmp(t.token_name, "id") == 0)
    {
        identifier_listPrime();
    }
    else
    {
        invalid();
    }
}

void identifier_listPrime()
{
    t = getNextToken();
    if (strcmp(t.token_name, ",") == 0)
    {
        identifier_list();
    }
    else if (strcmp(t.token_name, "[") == 0)
    {
        /* code */
        t = getNextToken();
        if (strcmp(t.token_name, "num") == 0)
        {
            t = getNextToken();
            if (strcmp(t.token_name, "]") == 0)
            {
                t = getNextToken();
                if (strcmp(t.token_name, ",") == 0)
                {
                    identifier_list();
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else if (strcmp(t.token_name, "[") == 0)
    {
        t = getNextToken();
        if (strcmp(t.token_name, "num") == 0)
        {
            t = getNextToken();
            if (strcmp(t.token_name, "]") == 0)
            {
                return;
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
}

void statement_list()
{
    t = getNextToken();
    char first[4][20] = {
        "id", "if", "while", "for"};

    int flag = 0;

    for (int i = 0; i < 4; i++)
    {
        /* code */
        if (strcmp(t.token_name, first[i]) == 0)
        {
            flag = 1;
        }
    }

    if (flag)
    {
        statement();
        statement_list();
    }
}

void statement()
{
    t = getNextToken();
    int flag = 0;

    if (strcmp(t.token_name, "id") == 0)
    {
        flag = 1;
    }
    else if (strcmp(t.token_name, "if") == 0)
    {
        flag = 2;
    }
    else if (strcmp(t.token_name, "while") == 0 || strcmp(t.token_name, "for") == 0)
    {
        flag = 3;
    }

    if (flag == 1)
    {
        assign_stat();
        // t = getNextToken();
        if (strcmp(t.token_name, ";") == 0)
        {
            return;
        }
    }
    else if (flag == 2)
    {
        /* code */
        decision_stat();
    }
    else if (flag == 3)
    {
        looping_stat();
    }
}
void assign_stat()
{
    t = getNextToken();
    if (strcmp(t.token_name, "id") == 0)
    {
        t = getNextToken();
        if (strcmp(t.token_name, "=") == 0)
        {
            expn();
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void expn()
{
    t = getNextToken();

    int flag = 0;
    if (strcmp(t.token_name, "id") == 0 || strcmp(t.token_name, "num") == 0)
    {
        flag = 1;
    }
    if (flag)
    {
        simple_exp();
        eprime();
    }
}

void eprime()
{
    t = getNextToken();
    char first[6][20] = {
        "==", "!=", "<=", ">=", ">", "<"};
    int flag = 0;

    for (int i = 0; i < 6; i++)
    {
        if (strcmp(t.token_name, first[i]) == 0)
        {
            flag = 1;
        }
    }

    if (flag)
    {
        relop();
        simple_exp();
    }
}

void simple_exp()
{
    // t = getNextToken();
    char first[2][20] = {
        "id", "num"};
    int flag = 0;

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(t.token_name, first[i]) == 0)
        {
            flag = 1;
        }
    }

    if (flag)
    {
        term();
        seprime();
    }
}

void seprime()
{
    t = getNextToken();
    int flag = 0;
    if (strcmp(t.token_name, "+") == 0 || strcmp(t.token_name, "-") == 0)
    {
        flag = 1;
    }
    if (flag)
    {
        addop();
        term();
        seprime();
    }
}

void term()
{
    t = getNextToken();
    char first[2][20] = {
        "id", "num"};
    int flag = 0;

    for (int i = 0; i < 2; i++)
    {
        /* code */
        if (strcmp(t.token_name, first[i]) == 0)
        {
            flag = 1;
        }
    }

    if (flag)
    {
        factor();
        tprime();
    }
}

void tprime()
{
    t = getNextToken();
    char first[3][20] = {
        "*", "/", "%"};
    int flag = 0;

    for (int i = 0; i < 3; i++)
    {
        /* code */
        if (strcmp(t.token_name, first[i]) == 0)
        {
            flag = 1;
        }
    }

    if (flag)
    {
        mulop();
        factor();
        tprime();
    }
}

void factor()
{
    t = getNextToken();
    if (strcmp(t.token_name, "id") == 0 || strcmp(t.token_name, "num") == 0)
    {
        return;
    }
}

void decision_stat()
{
    t = getNextToken();
    if (strcmp(t.token_name, "if") == 0)
    {
        t = getNextToken();
        if (strcmp(t.token_name, "(") == 0)
        {
            expn();
            t = getNextToken();
            if (strcmp(t.token_name, ")") == 0)
            {
                t = getNextToken();
                if (strcmp(t.token_name, "{") == 0)
                {
                    statement_list();
                    t = getNextToken();
                    if (strcmp(t.token_name, "}") == 0)
                    {
                        dprime();
                    }
                    else
                    {
                        invalid();
                    }
                }
                else
                {
                    invalid();
                }
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void dprime()
{
    t = getNextToken();
    if (strcmp(t.token_name, "else") == 0)
    {
        t = getNextToken();
        if (strcmp(t.token_name, "{") == 0)
        {
            statement_list();
            t = getNextToken();
            if (strcmp(t.token_name, "}") == 0)
            {
                return;
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void looping_stat()
{
    t = getNextToken();
    if (strcmp(t.token_name, "while") == 0)
    {
        t = getNextToken();
        if (strcmp(t.token_name, "(") == 0)
        {
            expn();
            t = getNextToken();
            if (strcmp(t.token_name, ")") == 0)
            {
                t = getNextToken();
                if (strcmp(t.token_name, "{") == 0)
                {
                    statement_list();
                    t = getNextToken();
                    if (strcmp(t.token_name, "}") == 0)
                    {
                        return;
                    }
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else if (strcmp(t.token_name, "for") == 0)
    {
        t = getNextToken();
        if (strcmp(t.token_name, "(") == 0)
        {
            assign_stat();
            t = getNextToken();
            if (strcmp(t.token_name, ";") == 0)
            {
                expn();
                t = getNextToken();
                if (strcmp(t.token_name, ";") == 0)
                {
                    assign_stat();
                    t = getNextToken();
                    if (strcmp(t.token_name, ")") == 0)
                    {
                        t = getNextToken();
                        if (strcmp(t.token_name, "{") == 0)
                        {
                            statement_list();
                            t = getNextToken();
                            if (strcmp(t.token_name, "}") == 0)
                            {
                                return;
                            }
                        }
                        else
                        {
                            invalid();
                        }
                    }
                    else
                    {
                        invalid();
                    }
                }
                else
                {
                    invalid();
                }
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void relop()
{
    t = getNextToken();
    if (strcmp(t.token_name, "==") == 0)
    {
        return;
    }
    else if (strcmp(t.token_name, "!=") == 0)
    {
        return;
    }
    else if (strcmp(t.token_name, "<=") == 0)
    {
        return;
    }
    else if (strcmp(t.token_name, ">=") == 0)
    {
        return;
    }
    else if (strcmp(t.token_name, ">") == 0)
    {
        return;
    }
    else if (strcmp(t.token_name, "<") == 0)
    {
        return;
    }
    else
        invalid();
}

void addop()
{
    t = getNextToken();
    if (strcmp(t.token_name, "+") == 0 || strcmp(t.token_name, "-") == 0)
    {
        return;
    }
    else
    {
        invalid();
    }
}
void mulop()
{
    t = getNextToken();
    if (strcmp(t.token_name, "*") == 0 || strcmp(t.token_name, "%") == 0 || strcmp(t.token_name, "/") == 0)
        return;
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

    fa = fopen("input.c", "r");
    fb = fopen("output.c", "w+");

    if (fa == NULL || fb == NULL)
    {
        printf("Can't open the file\n");
        exit(1);
    }

    preprocessing();

    t = getNextToken();

    program();

    printf("SUCCESS\n");

    return 0;
}
