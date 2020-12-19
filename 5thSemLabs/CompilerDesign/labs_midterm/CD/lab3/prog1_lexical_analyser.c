
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<ctype.h>

FILE * fa, *fb;

typedef struct prog1_lexical_analyser
{
    int row, col;
    char token_name[100];

} token;

// Makes token and returns 
token retToken(char * name, int row, int col)
{
    token t;
    
    strcpy(t.token_name,name);
    t.row=row;
    t.col=col;

    return t;
}


int isKeyword( char buffer[])
{
    char keywords[21][20]={
        "enum", "int","float", "return", "for",
         "while", "do", "return", "if", "else",
        "switch", "break", "continue", "struct", "typedef",
        "rigister", "double", "short", "union", "long", "unsigned"
    };

    for (int i = 0; i < 21; i++)
    {
        if(strcmp(keywords[i], buffer)==0)
        return 1;
    }

    return 0;
    
}

token getNextToken()
{

    char ca, cb;

    int r=1,c=1;

    char buff[100];
    int k=0;

    ca=getc(fa);
    c++;

    while (ca!=EOF)
    {

        if(ca=='\n')
        {
            r++;
            c=1;
        }


        if(isalpha(ca))
        {
            while (isalpha(ca) || ca=='_' || isdigit(ca))
            {
                buff[k++]=ca;
                ca=getc(fa);
            }
            buff[k]='\0';


            if(isKeyword(buff))
            {
                ca=getc(fa);
                return retToken(buff,r,c);

            }
            else if(ca=='[')
            {
                
                
            }
            
            
            
        }

    }
    

}

int main()
{
    fa=fopen("input.c","r");
    fb=fopen("output.c","w+");

    while (1)
    {
        token t=getNextToken();    
        if(t.token_name=="EOF")
        return 0;
        else  
        printf("%s (%d %d)", t.token_name,t.row,t.col);   
    }

    return 0;
    

}