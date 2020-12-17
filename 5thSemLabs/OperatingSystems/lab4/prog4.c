
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char * argv[])
{

	struct stat sb;
	int ret;
	char *new_path;

	if(argc<3)
	{
		fprintf(stderr,"usage:%s <old path> <new path> \n",argv[0]);
		return 1;
	}
	ret=symlink(argv[1],argv[2]);
	if(ret)
	{
		perror("symlink");
		return 1;
	}
	printf("File Linked \n");
	printf("New link %s\n",argv[2]);

	int ret2=unlink(argv[2]);
	if(ret2)
		perror("unlink");
	else
		printf("unlinked successfully\n");

	return 0;


}