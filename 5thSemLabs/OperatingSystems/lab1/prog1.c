
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
int main(int argc, char *argv[])
{
	
int fd;
int i=0;
int k=0;
char buf[100][100];
char ch;


fd=open("myFile.txt",O_RDONLY);
if(fd==-1)
{
	printf("Cant open the file\n");
	exit(1);
}
while((read(fd,&ch,1))==1)
{
	if(ch!='\n')
		{
			buf[k][i]=ch;
			i++;
		}
	else
		{
			buf[k][i]='\0';
			if(strstr(buf[k],argv[1])!=NULL)
			printf("line:%d %s\n",k+1,buf[k]);
			i=0;
			k++;
		}
}
}
