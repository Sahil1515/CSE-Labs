
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>

int main()
{
    char * myfifo_file="./myfifo";

    int fd;
    
   if(access(myfifo_file, F_OK) == -1){
		printf("pipe does not exist\n");
		fd = mkfifo(myfifo_file, 0777);
		if(fd != 0){
			fprintf(stderr, "could not create fifo %s\n", myfifo_file);
			exit(EXIT_FAILURE);
		}
	}

    char arr1[100], arr2[100];

    while (1)
    {

         int f1 = open(myfifo_file, O_RDONLY);
        read(f1,arr1,sizeof(arr1));
        printf("Kaustav: ");
        puts(arr1);
        close(f1);

        int f2 = open(myfifo_file, O_WRONLY);
        fgets(arr2,sizeof(arr2),stdin);
        write(f2,arr2,sizeof(arr2));
        close(f2);;
        
    }

return 0; 

}



