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



//2


#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

void printdir(char * dir, int depth)
{
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
			printf("%*s%s/\n",depth," ",entry->d_name);
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
		printdir("/usr/bin", 0);
		exit(0);
	}



#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
// #include<bits/stdc++.h>
// using namespace std;

int main(){
    DIR* mydir;
    char *c;
    int i;
    struct dirent *myfile;
    struct stat fileStat;

    mydir=opendir(".");
    
    while((myfile=readdir(mydir))!=NULL){
        if(strcmp(myfile->d_name,".")!=0 && strcmp(myfile->d_name,"..")!=0){
            lstat(myfile->d_name,&fileStat);
            printf("%s\n",myfile->d_name);
            printf("File Permission:\n");
            printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
            printf("\n");
        }
    }
    // int arr[5]={1,5,2,3,4};
    // sort(arr,arr+5);

    // for (int i = 0; i < 5; i++)
    // {
    //     printf("%d ", arr[i]);
    //     /* code */
    // }
    

    closedir(mydir);
    return 0;
}





//3




#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main()
{
    pid_t pid;
    pid=fork();
    if(pid==-1){
        printf("Fork failed\n");
        exit(0);
    }
    else if(pid==0)
    {
        printf("In Child:\n");
        for(int i=0;i<10;i++)
        {
            printf("Child process - %d\n",i+1); 
        }
        printf("Parent PID : %d\nChild PID : %d\n",getppid(),getpid());
        exit(0);
  }  
    else
    {
        printf("In Parent:\n");
        for(int i=0;i<2;i++)
            printf("Parent process - %d\n",i+1);
        sleep(10);
        int p=fork();
        if(p==0){
            printf("In child\n");
            sleep(1);
            printf("Parent pid : %d\n",getppid());
        }
        else{
        printf("Exiting parent\n");
        exit(0);
}
return 0;
}
}


#include<sys/types.h>
#include<sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
	pid_t pid;
	char * arr[]={"./prog1",NULL};
	pid =fork();

	if(pid==-1)
	{
		printf("Child not created\n");
	}
	else if(pid==0)
	{
		printf("I am child going to run the exec\n");
		execv(arr[0],arr);
		printf("This will not be executed\n");
		exit(0);
	}
	else {
		wait(NULL);
		printf("I am parent\n");
	}


}





//4



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char * argv[])
{

	struct stat sb;
	int ret;

	if(argc<2)
	{
		fprintf(stderr,"usage:%s <file> \n",argv[0]);
		return 1;
	}

	ret=stat(argv[1],&sb);
	if(ret)
	{
		perror("stat");
		return 1;
	}	

	printf("%ld\n",sb.st_ino);



}




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char * argv[])
{

	struct stat sb;
	int ret;
	char *new_path;

	if(argc<3)
	{
		fprintf(stderr,"usage:%s <old path> <new path> \n",argv[0]);
		return 1;
	}
	ret=symlink(argv[1],argv[2]);
	if(ret)
	{
		perror("symlink");
		return 1;
	}
	printf("File Linked \n");
	printf("New link %s\n",argv[2]);

	int ret2=unlink(argv[2]);
	if(ret2)
		perror("unlink");
	else
		printf("unlinked successfully\n");

	return 0;

}





// C program to read nth byte of a file and 
// copy it to another file using lseek 
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <fcntl.h> 

void func(char arr[], int n) 
{ 
	// Open the file for READ only. 
	int f_write = open("start.txt", O_RDONLY); 

	// Open the file for WRITE and READ only. 
	int f_read = open("end.txt", O_WRONLY); 

	int count = 0; 
	while (read(f_write, arr, 1)) 
	{ 
		// to write the 1st byte of the input file in 
		// the output file 
		if (count < n) 
		{ 
			// SEEK_CUR specifies that 
			// the offset provided is relative to the 
			// current file position 
			lseek (f_write, n, SEEK_CUR); 
			write (f_read, arr, 1); 
			count = n; 
		} 

		// After the nth byte (now taking the alternate 
		// nth byte) 
		else
		{ 
			count = (2*n); 
			lseek(f_write, count, SEEK_CUR); 
			write(f_read, arr, 1); 
		} 
	} 
	close(f_write); 
	close(f_read); 
} 

// Driver code 
int main() 
{ 
	char arr[100]; 
	int n; 
	n = 5; 

	// Calling for the function 
	func(arr, n); 
	return 0; 
} 

