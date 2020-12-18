// server program for udp connection
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 5002
#define MAXLINE 1000

// Server code
int main()
{
    int buffer[3];

    printf("hi");

    int send_back[3][3];
    int k=0;

    int servsockfd, len, n;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));

    // Create a UDP Socket
    servsockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    // bind server address to socket descriptor
    bind(servsockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while (1)
    {
        //receive the datagram
        len = sizeof(cliaddr);

        n = recvfrom(servsockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);
        // buffer[n] = '\0';

        if(n<=0)
        break;

        for (int i = 0; i < 3; i++)
        {
            /* code */
            send_back[k][i]=buffer[i];
        }
        k++;

        printf("server");
        
        // puts(buffer);
        //Echoing back to the client
    }
     sendto(servsockfd, send_back, n, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

    getchar();
    // close the descriptor
    close(servsockfd);
}
