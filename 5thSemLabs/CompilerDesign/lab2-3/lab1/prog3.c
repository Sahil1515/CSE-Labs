

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

char keyword_arr[32][10]=
						{

							"auto",	"break", "case",	"char",
							"const",	"continue",	"default",	"do",
							"double",	"else",	"enum",	"extern",
							"float",	"for",	"goto",	"if",
							"int", "long",	"register",	"return",
							"short",	"signed",	"sizeof",	"static",
							"struct",	"switch",	"typedef",	"union",
							"unsigned",	"void",	"volatile",	"while"

						};


  
int main()
{
	FILE *fa,*fb;

	fa=fopen("prog3InputFile.c","r");
	if(fa==NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	}

	fb=fopen("prog3OutputFile.c","w");
	if(fb==NULL)
	{
		printf("Cannot open the file\n");
		exit(0);
	}

	int ca,cb;
	char str[100];


	ca=getc(fa);

	while(ca!=EOF)
	{
		int k=0;
		while(isalpha(ca))
			{
				str[k++]=ca;
				ca=getc(fa);
			}
		str[k++]='\0';
		// printf("%s\n",str );
		
		int flag=0;
		for(int j=0;j<32;j++)
		{
			if(strcmp(str,keyword_arr[j])==0)
			{
				for(int i=0; str[i]!='\0'; i++)
   				{
        			if(str[i]>='a' && str[i]<='z')
        			{
            			str[i] = str[i] - 32;
        			}
        			flag=1;
    			}
    			if (flag==1)
    				printf("%s\n",str );
			}
		}
		ca=getc(fa);
	}
	fclose(fa);
	fclose(fb);

	return 0;


}
