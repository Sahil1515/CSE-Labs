

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include <dirent.h>
#include<sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{

    char str[100];
    printf("Enter the file name\n");
    scanf("%s",str);

    // chdir(".");

    struct stat s;
    lstat(str,&s);

    printf("%ld",s.st_ino);




}
