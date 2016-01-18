#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>
#include<unistd.h>

static void sig_usr(int signum)
{
	printf("signum is %d\n",signum);
}

int main()
{
	printf("pid %d\n",getpid());
	struct sigaction sa_usr;
	sa_usr.sa_flags=SA_SIGINFO;
	sa_usr.sa_handler=sig_usr;
	
	sigaction(36,&sa_usr,NULL);
	while(1)
	{
		sleep(1000); //saving cpu
	}
	return 0;
}

