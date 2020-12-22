#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    DIR * op = opendir(".");

    struct dirent *entry;
    struct stat statbuf;

    printf("\n\n");

    while ((entry = readdir(op)) != NULL)
    {
        /* code */
        lstat(entry->d_name, &statbuf);

        if (S_ISDIR(statbuf.st_mode))
        {
            continue;
        }
        else if (strstr(entry->d_name, ".c")!=NULL)
        {
            /* code */
            puts(entry->d_name);
        }
    }

    char name[100];

    printf("TO which file to give the permission\n");
    scanf(" %s",&name);

    op=opendir(".");
    while ((entry = readdir(op)) != NULL)
    {
        /* code */
        lstat(entry->d_name, &statbuf);

        if (S_ISDIR(statbuf.st_mode))
        {
            continue;
        }
        else if (strcmp(entry->d_name, name)==0)
        {
            statbuf.st_mode|=S_IRUSR|S_IWUSR;
            printf("done\n");
        }
    }
    // printf("%*s%s\n",depth,name);
    closedir(op);

    return 0;
}