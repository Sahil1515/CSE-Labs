
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main()
{
    struct dirent *entry;
    struct stat statbuf;

    chdir(".");

    DIR *op = opendir(".");

    while ((entry = readdir(op)) != NULL)
    {
        /* code */

        lstat(entry->d_name, &statbuf);

        // if(strcmp(entry->d_name,"prog1.c")==0)
        // {
        //     statbuf.st_mode|=S_IXUSR;
        //     printf("Done\n");
        // }

        if (S_ISDIR(statbuf.st_mode))
        {
            /* code */
            if (strcmp(".", entry->d_name) == 0 ||
                strcmp("..", entry->d_name) == 0)
            {
                continue;
            }
        }
        printf("%s ",entry->d_name);
        printf((statbuf.st_mode & S_IRUSR) ? "r" : "_");
        printf((statbuf.st_mode & S_IWUSR) ? "w" : "_");
        printf((statbuf.st_mode & S_IXUSR) ? "x" : "_");
        printf((statbuf.st_mode & S_IRGRP) ? "r" : "_");
        printf((statbuf.st_mode & S_IWGRP) ? "w" : "_");
        printf((statbuf.st_mode & S_IXGRP) ? "x" : "_");
        printf((statbuf.st_mode & S_IROTH) ? "r" : "_");
        printf((statbuf.st_mode & S_IWOTH) ? "w" : "_");
        printf((statbuf.st_mode & S_IXOTH) ? "x" : "_");
        printf("\n");

    }



}