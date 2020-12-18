#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<netinet/in.h>
#define LISTEN_BACKLOG 50

int main(int argc, char *argv[])
{
    int sfd, cfd;
    struct sockaddr_in my_addr, peer_addr;
    socklen_t peer_addr_size;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
        perror("socket");

   


    if (bind(sfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in)) == -1)
        perror("bind");

    if (listen(sfd, LISTEN_BACKLOG) == -1)
        perror("listen");

    /* Now we can accept incoming connections one
              at a time using accept(2) */
    peer_addr_size = sizeof(struct sockaddr_un);
    cfd = accept(sfd, (struct sockaddr *)&peer_addr,
                 &peer_addr_size);
    if (cfd == -1)
        handle_error("accept");

    /* Code to deal with incoming connection(s)... */

    /* When no longer required, the socket pathname, MY_SOCK_PATH
              should be deleted using unlink(2) or remove(3) */
}
