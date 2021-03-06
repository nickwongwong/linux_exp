#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>
#include<unistd.h>

static void sig_usr(int signum)
{
	if  (signum==SIGINT)
	{
		printf("signum is %d, ctrl+c\n",signum);
	} else
	if  (signum==SIGQUIT)
	{
		printf("signum is %d, ctrl+\\\n",signum);
	} 
}

int main()
{
	printf("pid %d\n",getpid());
	struct sigaction sa_usr;
	sa_usr.sa_flags=SA_SIGINFO;
	sa_usr.sa_handler=sig_usr;
	
	sigaction(SIGINT,&sa_usr,NULL); 
	sigaction(SIGQUIT,&sa_usr,NULL);
	while(1)
	{
		sleep(1000); //saving cpu
	}
	return 0;
}


