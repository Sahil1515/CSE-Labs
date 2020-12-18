

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<sys/types.h>

int main()
{
    int soc;

    struct sockaddr_in server, client;

    unsigned int len =sizeof(struct sockaddr_in);

    soc=socket(AF_INET, SOCK_STREAM,0);
    if(soc==-1)
    {
        perror("socket");
        exit(1);
    }
    
    server.sin_port=htons(10000);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    bzero(&server.sin_zero,8);


    if(bind(soc, (struct sockaddr *)&server ,len ) == -1){
        perror("bind");
        exit(0);
    }

    if(listen(soc,5)==-1)
    {
        perror("listen");
        exit(1);
    }

    int newSock;
     
    while (1)
    {
        /* code */

        if( (newSock=accept(soc,(struct sockaddr*)&client, len)) ==-1)
        {
            perror("accept");
            exit(1);
        }



    }
    



}