#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
int main(int argc, char const *argv[])
{
	
int fd;
int k=0;
char buf[100][100];
char ch;
if(argc!=2)
{
	printf("error\n");
	exit(0);
}
	fd=open(argv[1],O_RDONLY);
if(fd==-1)
{
	printf("Cant open the file\n");
	exit(0);
}
while(read(fd,&ch,1)==1)
{
	if(ch=='\n')
		{
		 k++;
		}
		printf("%c",ch);
		if(k==20)
		{
			while((read(0,&ch,1))!=1);
			k=0;
		}
}
return 0;

}
