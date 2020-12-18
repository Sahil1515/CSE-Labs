#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 5002
#define MAXLINE 1000

// Driver code
int main()
{
    int buffer[3][3];
    // char *message = "Hello Server";
    int rows[3][3]={
                {1,2,3},
                {4,5,6},
                {7,8,9}
    };

    printf("me ");


    int sockfd, n, len;
    struct sockaddr_in servaddr, cliaddr;

    // clear servaddr
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    // create datagram socket
       printf("Clientout1");
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Clientout");

    for (int i = 0; i < 3; i++)
    {
        printf("client");
        sendto(sockfd, rows[i], MAXLINE, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        len = sizeof(cliaddr);
    }

    // // waiting for response  
    n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);
    // buffer[n] = '\0';
    // printf("message fromser is %s \n", buffer);
    // getchar();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            /* code */
            printf("%d ",buffer[i][j]);
        }
        printf("\n");
        
        /* code */
    }
    

    // close the descriptor
    close(sockfd);
}
