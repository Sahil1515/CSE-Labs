fa = fopen("input.c", "r");
    // {
    //     printf("Cannot open file \n");
    //     exit(0);
    // }
    // fb = fopen("output.c", "w+");
    // ca = getc(fa);
    // while (ca != EOF)
    // {
    //     if (ca == ' ' || ca == '\t')
    //     {
    //         putc(' ', fb);
    //         while (ca == ' ' || ca == '\t')
    //             ca = getc(fa);
    //         ungetc(ca, fa);
    //     }
    //     else if (ca == '/')
    //     {
    //         cb = getc(fa);
    //         if (cb == '/')
    //         {
    //             while (ca != '\n')
    //                 ca = getc(fa);
    //         }
    //         else if (cb == '*')
    //         {
    //             do
    //             {
    //                 while (ca != '*')
    //                     ca = getc(fa);
    //                 ca = getc(fa);
    //             } while (ca != '/');
    //             ca = getc(fa);
    //         }
    //         else
    //         {
    //             putc(ca, fb);
    //             putc(cb, fb);
    //         }
    //     }
    //     else if (ca == '#')
    //     {
    //         while (ca != '\n')
    //         {
    //             ca = getc(fa);
    //         }
    //     }
    //     else
    //         putc(ca, fb);
    //     ca = getc(fa);
    // }
    // fclose(fa);
    // fclose(fb);