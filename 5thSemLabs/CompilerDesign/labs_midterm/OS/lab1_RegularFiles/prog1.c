

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

int main(char *argv[])
{
    int fd = open("samplefile.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }

    char buffer[1000];

    // int rd=read(fd,&buffer,sizeof(buffer));

    int i = 0;
    char ch;
    char * p;

    char *temp = argv[1];

    if ((p=strrchr(temp, '\n')) != NULL)
    {
        *p = '\0';
    }

    while (read(fd, &ch, 1) == 1)
    {
        if (ch != '\n')
        {
            buffer[i++] = ch;
        }
        else
        {
            buffer[i] = '\0';
            i = 0;
            if (strstr(buffer, temp) != NULL)
            {
                // puts(buffer);
                printf("%s ",buffer);
                // perror("strstr");
            }
        }
    }

    return 0;
}