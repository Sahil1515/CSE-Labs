#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

void printdir(char * dir, int depth)
{
// 	DIR * temp;
// 	temp=opendir(".");

// 	struct stat buff;
// 	chdir(dir);
// 	struct dirent * temp2= readdir(temp);

// 	lstat(temp2->d_name,&buff);

// 	printf("%s ",temp2->d_name);
// 	if(strcmp(".", temp2->d_name)==0 || strcmp("..", temp2->d_name)==0)
// 			return ;
// 	printdir(temp2->d_name,depth);

	DIR* dp;
	struct dirent* entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL)
	{
		fprintf(stderr, "cannot open directory: %s\n", dir);
		return;
	}
	chdir(dir);
	while((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name, &statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{
			if(strcmp(".", entry->d_name)==0 || strcmp("..", entry->d_name)==0)
			continue;
			printf("%s\n",entry->d_name);
			printdir(entry->d_name, depth+4);
		}
		else
			printf("%*s%s/\n", depth," ", entry->d_name);
	}
	chdir("..");
	closedir(dp);
	}
	
	int main(int argc, char const *argv[])
	{
		/* code */
		printdir(".", 0);
		exit(0);
	}
