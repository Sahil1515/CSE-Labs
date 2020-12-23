
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    FILE *fa = fopen("parseTable.c", "r");
    FILE *fb = fopen("outputParse.c", "w+");

    int ca = getc(fa);
    int cb;

    while (ca != EOF)
    {
        /* code */

        if (ca == '\n')
        {
            cb = getc(fa);
            if (cb == '\n')
            {
                continue;
            }
            else
            {
                putc(ca, fb);
                putc(cb, fb);
            }
        }
        else
        {
            putc(ca, fb);
        }

        ca = getc(fa);
    }

    return 0;
}