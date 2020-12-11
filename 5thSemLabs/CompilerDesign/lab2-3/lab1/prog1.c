

#include <stdio.h>
#include<stdlib.h>

int main()
{
	FILE *fa,*fb;

	fa=fopen("prog1InputFile.c","r");
	if(fa==NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	}

	fb=fopen("prog1OutputFile.c","w");
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
			while(ca==' ' || ca=='\t')
				ca=getc(fa);
		}
		if(ca=='\t')
		{
			putc(ca,fb);
			while(ca==' ' || ca=='\t')
				ca=getc(fa);
		}
			putc(ca,fb);
		ca=getc(fa);

	}
	fclose(fa);
	fclose(fb);

	return 0;


}