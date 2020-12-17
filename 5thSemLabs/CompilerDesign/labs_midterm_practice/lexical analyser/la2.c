#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct token
{
    /* data */
    int row, col;
    char token_name[100];
} token;

typedef struct ste
{
    /* data */
    char lexeme[100];
    int index;
    char type[100];
    int size;

} ste;

FILE *fa, *fb;
ste Table[100];
int r = 1, c = 1;

int STindex = 0;

token newToken(int r, int c, char lexeme[100])
{
    token t;

    t.row = r;
    t.col = c;
    strcpy(t.token_name, lexeme);

    return t;
}
void insertSTE(char buffer[100])
{
    ste t;
    t.index = STindex + 1;
    strcpy(t.lexeme, buffer);
    t.size = 4;
    strcpy(t.type, "int");

    for (int i = 0; i < STindex; i++)
    {
        if (strcmp(buffer, Table[STindex].lexeme) == 0)
            return;
    }

    Table[STindex++] = t;
}

void printST()
{
    for(int i=0;i<STindex;i++)
    {
        printf("%d %s %s %d\n", i+1,Table[STindex].lexeme,Table[STindex].type,Table[STindex].size);

    }
}

int isKeyword(char *word)
{
    char *keylist[2] = {"scalar", "foreach"};
    for (int i = 0; i < 2; ++i)
    {
        if (strcmp(word, keylist[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int isOperator(char ca)
{
    return (strchr("+-/", ca) != NULL);
}
int isSpecialSymbol(char ca)
{
    return (strchr("@_", ca) != NULL);
}

token getNextToken()
{
    char ca = getc(fa);
    c++;

    char buffer[100];
    int k = 0;

    if (ca == EOF)
        return newToken(r, c, "EOF");

    while (ca == '\n')
    {
        /* code */
        ca = getc(fa);
        r++;
        c = 1;
    }

    if (ca == '$')
    {
        /* code */
        ca = getc(fa);
        while (isalpha(ca))
        {
             buffer[k++] = ca;
            ca = getc(fa);
            c++;
        }
        buffer[k] = '\0';
        ungetc(ca, fa);
        c--;

        if (isKeyword(buffer))
        {
            return newToken(r, c - strlen(buffer) + 1, buffer);
        }
        else
        {

            insertSTE(buffer);
            return newToken(r, c - strlen(buffer) + 1, buffer);
        }
    }
    else
    {
        if (isSpecialSymbol(ca))
        {
            buffer[k++] = ca;
            buffer[k] = '\0';
            return newToken(r, c, buffer);
        }
        else if (isOperator(ca))
        {
            buffer[k++] = ca;
            ca = getc(fa);
            c++;
            if (ca == '=')
            {
                buffer[k++] = ca;
            }
            else
            {
                ungetc(ca, fa);
                c--;
            }
            buffer[k] = '\0';
            return newToken(r, c - strlen(buffer) + 1, buffer);
        }
    }
}

int main()
{
    fa = fopen("input.pl", "r");
    fb = fopen("output.pl", "w+");
    if (fa == NULL || fb == NULL)
    {
        printf("Can't open the file\n");
        exit(1);
    }

    char ca = getc(fa);

    while (ca != EOF)
    {
        /* code */
        if (ca == '#')
        {
            while (ca != '\n')
            {
                /* code */
                ca = getc(fa);
            }
        }
        else
        {
            putc(ca, fb);
        }
        ca=getc(fa);
    }

    fclose(fa);
    fclose(fb);

    fa = fopen("output.pl", "r");
    if (fa == NULL)
    {
        printf("Can't open the file\n");
        exit(1);
    }

    while (1)
    {
        /* code */
        token t = getNextToken();

        if (strcmp(t.token_name, "EOF") == 0)
            break;
        else
        {
            printf("< %s %d %d >\n", t.token_name, t.row, t.col);
        }
    }
    printST();
    return 0;
}