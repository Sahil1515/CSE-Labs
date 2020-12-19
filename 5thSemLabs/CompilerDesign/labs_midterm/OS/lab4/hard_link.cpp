

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

int main(int argc, char *argv[])
{
    char * path = argv[1];

    int dir = mkdir("newdir",S_IRUSR);
    if(link(path,"agar")==0)
    perror("link");
    symlink(path,"Sahil");

    chdir(".");
    rmdir("sahil");

    return 0;

}