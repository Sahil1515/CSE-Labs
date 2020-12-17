//Server program
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
int main()
{
	int sd,nd,n,len,reult;
	struct sockaddr_in seraddress, cliaddr;
	sd=socket(AF_INET, SOCK_STREAM,0);
	seraddress.sin_family=AF_INET;
	seraddress.sin_addr.s_addr=INADDR_ANY;
	seraddress.sin_port=htons(10200);
	bind(sd,(struct sockaddr*)&seraddress,sizeof(seraddress));
	listen(sd,5);
	len=sizeof(cliaddr);

		int s=0;
		while(1)
		{
			s++;
		char buff[100];

		nd=accept(sd,(struct sockaddr*)&cliaddr,&len);

		if (fork()==0){
			close(sd);
		
		// printf("Forked\n");
		read(nd,buff,100);

		char result[100];
		// printf("%c\n",buff[2]);
		switch(buff[2])
		{
			case '+': result[0] = (buff[0])+(buff[1]);
			break;
			case '-': result[0] = (buff[0])-(buff[1]);
			break;
			case '*': result[0] = (buff[0])*(buff[1]);
			break;
			case '/': result[0] = (buff[0])/(buff[1]);
			break;
			
		}
		write(nd, result, 100);
		close(nd);

		}
		if(s>10)
			exit(0);
		
	    }
		
}

