#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>  
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

struct msg_data
{
	long mtype;
	char mtext[110];	
};

int main()
{
	int msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
	if (msgid==-1) printf("creat msg fail");
	printf("msgid %d\n",msgid);
	int type;

	while(1)
	{
		printf("input command 0 to send, 1 to receive\n");
		scanf("%d",&type);getchar();

		if (type==0) //send
		{
			struct msg_data data={1,"I Like Linux!"};
			printf("input message to send\n");
			//scanf("%s",data.mtext);
			gets(data.mtext);
			if (msgsnd(msgid,&data,sizeof(data),IPC_NOWAIT)==-1) printf("failed to send\n"); else
				printf("success to send\n");	
		} else
			if (type==1) //receive
			{
				struct msg_data data;
				printf("input msgid\n");
				int msgid_receive;
				scanf("%d",&msgid_receive);
				if (msgrcv(msgid_receive,&data,sizeof(data),1,IPC_NOWAIT)==-1) printf("failed to receive\n"); else
				{
					printf("success to receive\n");
					printf("receive %s\n",data.mtext);
				}
			}
	}
	megctl(msgid,IPC_RMID,NULL);
	return 0;
}
