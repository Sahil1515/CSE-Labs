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

	printf("Stat structure of %s :\n",argv[1] );
	printf("Id of device :%ld\n",sb.st_dev);
	printf("Inode number:%ld\n",sb.st_ino);
	printf("Permissions :%u\n",sb.st_mode);
	printf("Number of hard links :%ld\n",sb.st_nlink);
	printf("User id of owner :%u\n",sb.st_uid);
	printf("Group id of owner :%u\n",sb.st_gid);
	printf("Device id if special file :%ld\n",sb.st_rdev);
	printf("Totaol size of the file :%ld\n",sb.st_size);
	printf("Block size:%ld\n",sb.st_blksize);
	printf("Number of blocks:%ld\n",sb.st_blocks);
	printf("Last access time:%ld\n",sb.st_atime);
	printf("Last modification time :%ld\n",sb.st_mtime);
	printf("Last status change time:%ld\n",sb.st_ctime);


	return 0;

}