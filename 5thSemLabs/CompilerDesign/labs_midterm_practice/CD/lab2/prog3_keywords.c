
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

FILE *fa, *fb;

int main()
{
    fa = fopen("output2.c", "r");

    if(fa==NULL)
    {
        printf("Can't open the file\n");
        exit(1);
    }

    char ca, cb;

    char keywords[21][20] = {
        "int", "long", "unsigned", "else", "if", "double",
        "float", "enum", "char", "while", "for", "do", "short",
        "return", "switch", "struct", "union", "typedef", "auto",
        "break", "continue"};

    ca = getc(fa);

      char buffer[100];
    while (ca != EOF)
    {
        int i = 0;

        if (isalpha(ca))
        {
            while (isalpha(ca))
            {
                buffer[i++] = ca;
                ca = getc(fa);
            }
             ungetc(ca, fa);
        }
       
        buffer[i] = '\0';

        for (int i = 0; i < 21; i++)
        {
            if(strstr(buffer, keywords[i]) !=NULL)
            {
                printf("%s\n", buffer);
                break;
            }
        }

        ca = getc(fa);
    }

    return 0;
}