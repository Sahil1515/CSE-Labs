#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main()
{
    pid_t p=fork();
    if(p==-1)
    {
        printf("Can't crete the process\n");
        exit(1);
    }
    else if(p==0)
    {
        printf("Child process\n");
        printf("%d pid \n",getppid());
        sleep(3);
        printf("%d pid \n",getppid());
    }
    else
    {
        sleep(2);
        printf("Parent\n");
        exit(1);
    }
    
return 0;

}








// #include <stdlib.h> 
// #include <sys/types.h> 
// #include <unistd.h> 
// int main() 
// { 
//     // Fork returns process id 
//     // in parent process 
//     pid_t child_pid = fork(); 
  
//     // Parent process  
//     if (child_pid > 0) 
//         sleep(5); 
  
//     // Child process 
//     else        
//         exit(0); 
  
//     return 0; 
// } 


// A C program to demonstrate Orphan Process. 
// Parent process finishes execution while the 
// child process is running. The child process 
// becomes orphan. 
// #include<stdio.h> 
// #include <sys/types.h> 
// #include <unistd.h> 

// int main() 
// { 
// 	// Create a child process	 
// 	int pid = fork(); 

// 	if (pid > 0) 
// 		printf("in parent process"); 

// 	// Note that pid is 0 in child process 
// 	// and negative if fork() fails 
// 	else if (pid == 0) 
// 	{ 
// 		sleep(3); 
// 		printf("in child process");
//         printf("%d pid ",getppid()); 
// 	} 

// 	return 0; 
// } 
