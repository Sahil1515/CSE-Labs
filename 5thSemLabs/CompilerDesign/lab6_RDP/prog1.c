
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
S-->a | > | ( T )
T-->T, S|S
*/

int cur=0;
char str[100];

void S();
void T();


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

void S()
{
	if(str[cur]=='a')
	{
		cur++;
		return;
	}
	else if(str[cur]=='>')
	{
		cur++;
		return;
	}
	else if(str[cur]=='(')
	{
		cur++;
		T();
		if(str[cur]==')')
		{
			cur++;
			return;
		}
		else Invalid();
	}
	else Invalid();
}

void T()
{
	T();
	if(str[cur]==',')
	{
		cur++;
		S();
		return;
	}
	else S();

}
int main()
{
	printf("Enter the string\n");
	scanf("%s",str);

	S();

	if(str[cur]=='$')
		Valid();
	else Invalid();

	return 0;
}