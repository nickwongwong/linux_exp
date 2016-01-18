#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#define DATA_SIZE 1024
struct shm_data
{
	int fresh; //1 to read, 0 to write
	char text[DATA_SIZE]; //text
};

void toread(struct shm_data *data) //read
{
	//printf("%d\n",data->fresh);
	if (data->fresh==1)
	{
		printf("get data: %s",data->text);
		data->fresh=0;
	}
	usleep(100); //sleep for 100ms 
}

void towrite(struct shm_data * data) //write
{
	puts("input message to send");
	fgets(data->text, DATA_SIZE, stdin);
	data->fresh=1;
	puts("succeed to send\n");
}

int main()
{
	int shmid = shmget((key_t)666, sizeof(struct shm_data), 0666 | IPC_CREAT); //create a shared memory named 666 
	if (shmid==-1)
	{
		printf("shmget failed\n");
	}

	void *shm = shmat(shmid, (void *)0, 0); //attach to current process
	if (shm==(void *)-1)
	{
		printf("shmat failed\n");
	}
	printf("attach at %x\n",(int) shm); 

	struct shm_data *data = (struct shm_data *)shm;
	data->fresh=0; //need to write

	puts("input 0 to read or 1 to write"); //command
	int type;
	scanf("%d",&type);getchar();
	while(1)
	{
		if (type==0) toread(data); else towrite(data);
	}
	return 0;
}
