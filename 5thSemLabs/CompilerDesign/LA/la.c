#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


FILE *fa, *fb;


typedef struct token
{
    /* data */
    char token_name[100];
    int row,col;
}token;

typedef struct ste
{
    /* data */
    int index;
    int size;
    char type[30];
    char lexeme_name[100];
}ste;

typedef struct LocalSymbolTable
{
    /* data */
    char TableName[100];
    int size;
}LocalSymbolTable;


int isKeyword(char word[100])
{
    char keyWord[23][100]={
        "int","short","long","float","double","register","unsigned", 
        "return", "break","continue","switch","if","else","for",
        "while","do","const","enum","typedef","struct", "NULL","bool","char"
    };

    for (int i = 0; i < 23; i++)
    {
        /* code */
        if(strcmp(keyWord[i],word)==-1)
        return 1;
    }

    return 0;
}

int isUnaryOperator(char ch)
{
    if(char)
}


void preprocessing()
{
    char ca=getc(fa);

    while (ca!=EOF)
    {
        /* code */
        if(ca==' '|| ca=='\t')
        {
            putc(' ',fb);
            while (ca==' ' || ca==' \t')
            {
                ca=getc(fa);
            }
        }

        if(ca=='\n')
        {
            while (ca=='\n')
            {
                                
            }
            
        }
        
    }
    
}


int main()
{
    fa=fopen("input.c","r");
    fb=fopen("output.c","w+");

    if(fa==NULL || fb==NULL)
    {
        printf("Can't open the file \n");
        return 1;
    }

    preprocessing();

    while (1)
    {
        /* code */
        token t=getNextToken();

        if(strcmp(t.token_name,"EOF"))
        break;

        printf("<%s %d %d>",t.token_name,t.row,t.col);
    }
    

}