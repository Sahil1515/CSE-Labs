#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct token
{
    int row, col;
    char token_name[100];
} token;

typedef struct ste
{
    /* data */
    int index;
    int size;
    char lexeme[100];
    char type[100];
} ste;

typedef struct localTableData
{
    int size;
    char func[100];
} localTableData;

int r = 1;
int c = 1;

int scope = 0;
int st_num = -1;
int st_index = 0;

ste Table[10][100];
localTableData TableMetaData[10];

token NewToken(int row, int col, char token_anme[100])
{
    token t;
    strcpy(t.token_name, token_anme);
    t.row = row;
    t.col = col;

    return t;
}

void printST()
{
}

void insertST(char buff[], char dbuf[], int size)
{
    ste t;
    strcpy(t.lexeme, buff);
    strcpy(t.type, dbuf);
    t.index = st_index + 1;
    t.size = size;

    for (int i = 0; i < st_index; i++)
    {
        /* code */
        if (strcmp(Table[st_num][i].lexeme, buff) == 0)
            return;
    }
    st_index++;
    Table[st_num][st_index] = t;
    TableMetaData[st_num].size += 1;
}

void STprint()
{
    for (int i = 0; i <=st_num; i++)
    {
        /* code */
        printf("Symbol Table for %s :\n\n", TableMetaData[i].func);
        printf("Index\tLexeme\tType\tSize\n");

        for (int j = 0; j <=TableMetaData[i].size; j++)
        {
            /* code */
            printf("%d\t%s\t%s\t%d\n", Table[i][j].index, Table[i][j].lexeme,
                   Table[i][j].type, Table[i][j].size);
        }

        printf("\n");
    }

}

int isKeyword(char buff[100])
{
    char keywords[13][100] = {
        "int", "short", "typedef", "enum", "char", "return", 
        "if", "else", "break", "continue","void", "sizeof", "printf"};

    for (int i = 0; i < 13; i++)
    {
        /* code */
        if (strcmp(buff, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
int iscombined(char buff[100])
{
    char keywords[2][100] = {
        "++", "--"};

    for (int i = 0; i < 8; i++)
    {
        /* code */
        if (strcmp(buff, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch)
{
    return (strchr("+-/%*<>!=^", ch) != NULL);
}
int isSpecialSymbol(char ch)
{
    return (strchr("[]{}(),.:;#$@", ch) != NULL);
}

token getNextToken(FILE *fa)
{

    token t;
    char buff[100];
    char dbuf[100];
    int k = 0;

    int ca = getc(fa);
    c++;

    while (ca == '\n')
        strcpy(dbuf, ""), r++, ca = getc(fa), c = 0;

    if (ca == EOF)
        return NewToken(r, c, "EOF");

    while (ca == ' ')
        ca = getc(fa), c++;

    if (isalpha(ca))
    {
        while (isalpha(ca) || isdigit(ca) || ca == '_')
        {
            buff[k++] = ca;
            ca = getc(fa);
            c++;
        }
        ungetc(ca, fa);
        c--;
        buff[k] = '\0';

        if (isKeyword(buff))
        {
            strcpy(dbuf, buff);
            return NewToken(r, c - strlen(buff) + 1, buff);
        }
        else
        {
            // printf("%s \n", buff);
            if (strcmp(buff, "main") == 0)
                t = NewToken(r, c - strlen(buff) + 1, "main");
            else
            {
                t = NewToken(r, c - strlen(buff) + 1, "id");
            }

            ca = getc(fa);
            if (ca == '(')
            {
                if (scope != 0)
                {
                    insertST(buff, "func", -1);
                }
                else
                {
                    /* code */
                    st_num++;
                    strcpy(TableMetaData[st_num].func, buff);
                    st_index = 0;
                }
                ungetc(ca, fa);
                return t;
            }

            int size = 0;
                int num = 0;


            if (ca == '[')
            {
                //Array
                int pos = ftell(fa);

                int cb = getc(fa);
                while (cb != ']')
                {
                    /* code */
                    num = num * 10 + (cb - '0');
                    cb = getc(fa);
                }
                fseek(fa, pos, SEEK_SET);
                ungetc(ca, fa);

            }
            if (strcmp(dbuf, "int") == 0 || strcmp(dbuf, "float") == 0)
                size = 4;
            else if (strcmp(dbuf, "bool") == 0 || strcmp(dbuf, "char") == 0)
                size = 1;
            else if (strcmp(dbuf, "double") == 0 || strcmp(dbuf, "long") == 0)
                size = 8;
            if(num==0)
            num=1;

            insertST(buff, dbuf, size * num);
            return t;
        }
    }
    else if (isdigit(ca))
    {
        /* code */

        while (isdigit(ca) || ca == '.' || ca == 'e' || ca == 'E')
        {
            /* code */
            ca = getc(fa);
            c++;
        }
        ungetc(ca, fa);

        return NewToken(r, c - strlen(buff) + 1, "num");
    }
    else if (ca == '"')
    {
        /* code */
        ca = getc(fa);
        c++;
        while (ca != '"')
        {
            /* code */
            buff[k++] = ca;
            ca = getc(fa);
            c++;
        }
        buff[k] = '\0';
        return NewToken(r, c - strlen(buff) + 1, "string");
    }

    else if (isSpecialSymbol(ca))
    {

        buff[k++] = ca;
        if (ca == '{')
            scope++;
        else if (ca == '}')
            scope--;

        buff[k] = '\0';
        return NewToken(r, c - strlen(buff) + 1, buff);
    }
    else if (isOperator(ca))
    {
        buff[k++] = ca;

        ca = getc(fa);
        c++;
        if (ca == '=')
        {
            buff[k++] = ca;
        }
        else
        {
            ungetc(ca, fa);
            c--;
        }
        buff[k] = '\0';
        return NewToken(r, c - strlen(buff) + 1, buff);
    }
    else if (ca == '&')
    {
        buff[k++] = ca;

        ca = getc(fa);
        c++;
        if (ca == '&')
        {
            buff[k++] = ca;
        }
        else
        {
            ungetc(ca, fa);
            c--;
        }
        buff[k] = '\0';
        return NewToken(r, c - strlen(buff) + 1, buff);
    }
    else if (ca = '|')
    {
        buff[k++] = ca;

        ca = getc(fa);
        c++;
        if (ca == '|')
        {
            buff[k++] = ca;
        }
        else
        {
            ungetc(ca, fa);
            c--;
        }
        buff[k] = '\0';
        return NewToken(r, c - strlen(buff) + 1, buff);
    }
}

void preprocess(FILE *fa, FILE *fb)
{

    int ca = getc(fa);
    int cb;

    while (ca != EOF)
    {
        //Tabs and spaces
        if (ca == ' ' || ca == '\t')
        {
            putc(' ', fb);
            while (ca == ' ' || ca == '\t')
            {
                /* code */
                ca = getc(fa);
            }
            ungetc(ca, fa);
        }

        //comments

        else if (ca == '/')
        {
            c++;
            int cb = getc(fa);
            if (cb == '/')
            {
                while (cb != '\n')
                {
                    /* code */
                    cb = getc(fa);
                    c++;
                }
            }
            else if (cb == '*')
            {
                /* code */
                do
                {
                    while (cb != '*')
                    {
                        cb = getc(fa);
                    }
                    cb = getc(fa);
                } while (cb != '/');

                ca = getc(fa);
            }
            else
            {
                putc(ca, fb);
                putc(cb, fb);
            }
        }

        //Directives
        else if (ca == '#')
        {
            while (ca != '\n')
            {
                ca = getc(fa);
            }
        }
        else
        {
            putc(ca, fb);
        }
        ca = getc(fa);
    }
}

int main()
{
    // printf("hey1");

    FILE *fa, *fb;

    fa = fopen("input.c", "r");
    if (fa == NULL)
    {
        printf("Can't open the file\n");
        exit(1);
    }
    fb = fopen("output.c", "w+");

    if (fb == NULL)
    {
        printf("Can't open the file\n");
        exit(1);
    }
    // printf("hey");

    preprocess(fa, fb);

    fclose(fa);
    fclose(fb);

    fa = fopen("output.c", "r");
    if (fa == NULL)
    {
        printf("Can't open the file\n");
        exit(1);
    }

    while (1)
    {
        token t = getNextToken(fa);

        if (strcmp(t.token_name, "EOF") == 0)
        {
            break;
        }

        printf("<%d %d %s>\n", t.row, t.col, t.token_name);
    }

    STprint();
    
    return 0;
}