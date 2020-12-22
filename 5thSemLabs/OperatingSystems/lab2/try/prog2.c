
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#define PATH "/home/sahil/Desktop/CSE-Labs/5thSemLabs"

void dirDig(char *dir, int depth)
{
    struct dirent *entry;
    struct stat statbuf;

    DIR *op = opendir(dir);

    chdir(dir);

    if (op == NULL)
    {
        printf("Can't open ");
        exit(1);
    }
    while ((entry = readdir(op)) != NULL)
    {
        lstat(entry->d_name, &statbuf);

        if (S_ISDIR(statbuf.st_mode))
        {
            if (strcmp(".", entry->d_name) == 0 ||
                strcmp("..", entry->d_name) == 0)
            {
                continue;
            }
            else
            {
                dirDig(entry->d_name, depth+3);
            }
        }
        printf("%*s%s/\n",depth," ",entry->d_name);
        // printf((statbuf.st_mode & S_IRUSR) ? "r" : "_");
        // printf((statbuf.st_mode & S_IWUSR) ? "w" : "_");
        // printf((statbuf.st_mode & S_IXUSR) ? "x" : "_");
        // printf((statbuf.st_mode & S_IRGRP) ? "r" : "_");
        // printf((statbuf.st_mode & S_IWGRP) ? "w" : "_");
        // printf((statbuf.st_mode & S_IXGRP) ? "x" : "_");
        // printf((statbuf.st_mode & S_IROTH) ? "r" : "_");
        // printf((statbuf.st_mode & S_IWOTH) ? "w" : "_");
        // printf((statbuf.st_mode & S_IXOTH) ? "x" : "_");

        // printf("\n");
    }
    chdir("..");
}

int main()
{
    dirDig(PATH, 1);
    return 0;
}