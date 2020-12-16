#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<bits/stdc++.h>
using namespace std;

int main()
{
    DIR * dir=opendir(".");

    string arr[100];

    if(dir==NULL)
    {
        printf("Cant open");
        return 0;
    }

    int i=0;

    struct dirent *d;
    while ( (d=readdir(dir)) !=NULL)
    {
        struct stat s;

        if(strcmp(".",d->d_name)==0 || strcmp("..",d->d_name)==0)
        continue;

        cout<<d->d_name;
        printf("\n");
        lstat(d->d_name,&s);
        if(S_ISDIR(s.st_mode))
        arr[i]=d->d_name,i++;
        

    }
    
    sort(arr, arr+i);

printf("\n\n\n");

    for(int j=0;j<i;j++)
    {
        cout<<arr[j];
        printf("\n");
    }

return 0;

}