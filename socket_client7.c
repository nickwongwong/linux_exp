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
	int sockfd, n;
    char recvline[MAXLINE], sendline[MAXLINE];
    struct sockaddr_in servaddr;	

	if ( argc != 2) //ip address
	{
		printf("need for server ip address, usage: ./client <ipaddress>\n");
		exit(1);
	}

	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) //create socket
	{
		printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
		exit(1);
    }	

	memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) //onvert IPv4 and IPv6 addresses from text to binary form
	{
		printf("inet_pton error for %s\n",argv[1]);
		exit(1);
    }
	
	//don't need bind for cliet
	if ( connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) //connect
	{
		printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
		exit(1);
	}

	printf("send msg to server: \n");
    fgets(sendline, 4096, stdin);
    if( send(sockfd, sendline, strlen(sendline), 0) < 0) //send
    {
		printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
    }

	close(sockfd);
	return 0;
}
