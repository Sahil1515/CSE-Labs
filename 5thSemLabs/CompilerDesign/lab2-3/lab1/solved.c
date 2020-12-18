

#include <stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fa,*fb;

	fa=fopen("solvedInputFile.c","r");
	if(fa==NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	}

	fb=fopen("solvedOutputFile.c","w");
	if(fb==NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	}

	int ca,cb;

	ca=getc(fa);

	while(ca!=EOF)
	{
		if(ca==' ')
		{
			putc(ca,fb);
			while(ca==' ')
				ca=getc(fa);
		}

		if(ca=='/')
		{
			cb=getc(fa);
			if(cb=='/')
				while(ca!='\n')
					ca=getc(fa);
			else if(cb=='*')
			{
				ca=getc(fa);
				ca=getc(fa);
				cb=getc(fa);
				while(ca!='*' && cb!='\\')
				{
					ca=getc(fa);
					cb=getc(fa);
				}
			}
			else
			putc(ca,fb);
		}
		else putc(ca,fb);
		ca=getc(fa);

	}
	fclose(fa);
	fclose(fb);

	return 0;


}