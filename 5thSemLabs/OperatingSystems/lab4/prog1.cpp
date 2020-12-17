
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char * argv[])
{

	struct stat sb;
	int ret;

	if(argc<2)
	{
		fprintf(stderr,"usage:%s <file> \n",argv[0]);
		return 1;
	}

	ret=stat(argv[1],&sb);
	if(ret)
	{
		perror("stat");
		return 1;
	}	

	printf("%ld\n",sb.st_ino);



}
