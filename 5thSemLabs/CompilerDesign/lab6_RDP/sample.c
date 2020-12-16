
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
E --> TEprime
E' --> +TE' / ε
T --> FT'
T' --> *FT' / ε
F --> (E) / i
*/

int cur=0;
char str[100];

void E();
void EPrime();
void T();
void F();
void TPrime();
void Valid();
void Invalid();

void Valid()
{
	printf("Valid String \n");
	exit(0);
}

void Invalid()
{
	printf("Invalid String %s\n",str );
	exit(0);
}
void E()
{
	T();
	EPrime();
}

void EPrime()
{
	if(str[cur]=='+')
	{
		cur++;
		T();
		EPrime();
	}
}

void T()
{
	F();
	TPrime();
}

void TPrime()
{
	if(str[cur]=='*')
	{
		cur++;
		F();
		TPrime();
	}
}
void F()
{
	if(str[cur]=='(')
	{
		cur++;
		E();
		if(str[cur]==')')
		{
			cur++;
			return;
		}
		else
			Invalid();
	}
	else if(str[cur]=='i')
	{
		cur++;
		return;
	}
	else Invalid();

}

int main()
{
	printf("Enter the string\n");
	scanf("%s",str);

	E();

	if(str[cur]=='$')
		Valid();
	else Invalid();

	return 0;
}