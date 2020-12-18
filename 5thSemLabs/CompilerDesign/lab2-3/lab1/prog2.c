

#include <stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fa,*fb;

	fa=fopen("prog2InputFile.c","r");
	if(fa==NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	}

	fb=fopen("prog2OutputFile.c","w");
	if(fb==NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	}

	int ca,cb;

	ca=getc(fa);
	while(ca!=EOF)
	{
		if(ca=='#')
		{
			while(ca!='\n')
				ca=getc(fa);
		}
		else 
			putc(ca,fb);

		ca=getc(fa);

	}
	fclose(fa);
	fclose(fb);

	return 0;


}