#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"

token t;

FILE *fa, *fb;

void program();
void declarations();
void data_type();
void identifier_list();
void identifier_listPrime();
void statement_list();
void statement();
void assign_stat();
void expn();
void exprime();
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
    printf("Error at %d %d ", t.row,t.col);
    exit(1);
} 

void program()
{
    if(strcmp(t.token_name,"main")==0)
    {
        t=getNextToken();
        if(strcmp(t.token_name,"(")==0)
        { 
            t=getNextToken();
            if(strcmp(t.token_name,")")==0)
            {
                t=getNextToken();
                if(strcmp(t.token_name,"{")==0)
                {

                    declarations();
                    statement_list();
                    if (strcmp(t.token_name,"}")==0)
                    {
                        return;
                        
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
    else 
    {
        invalid();
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

    fa = fopen("input.c", "r");    
    fb = fopen("output.c", "w+");    

    if (fa == NULL || fb == NULL)
    {
        printf("Can't open the file\n");        
        exit(1);        
    }

    preprocessing();

    t=getNextToken();

    program();

    printf("SUCCESS\n");
    
    return 0;

}
