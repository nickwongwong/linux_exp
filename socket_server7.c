#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 4096

int main(int argc, char **argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	int n;

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) //create socket
	{
		printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
		exit(1);
	}
	
	//set parameters 
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(6666);

	if ( bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) //blind socket
	{
		printf("bind socket error: %s(errno: %d)\n", strerror(errno),errno);
		exit(1);
	}

	if ( listen(listenfd, 10) == -1) //listen socket
	{
		printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
		exit(1);
	}

	printf("========waiting for client's connect=======\n");
	while(1)
	{
		if ( (connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) == -1) //accept
		{
			printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
			continue;
		}
		int n = recv(connfd, buff, MAXLINE, 0); //receive
		buff[n]='\0';
		printf("recv msg from client: %s\n", buff);
		close(connfd);
	}

	close(listenfd);
	return 0;
}
