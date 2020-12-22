
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int in =open("myFile.txt",O_RDONLY);
	int out=open("myOutFile.txt",O_WRONLY);

	char ch[10];
	// read(in,&ch,1);
	while(read(in,&ch,1)==1)
	{
		write(out,&ch,1);
	}

	return 0;
}