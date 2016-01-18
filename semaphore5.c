//gcc semaphore.c -o semaphore -pthread
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
sem_t sem;

void * Consumer(void *arg)
{
	printf("Consumer wait semaphore %d\n",(int)sem.__align);
	sem_wait(&sem);
	printf("Consumer end semaphore %d\n",(int)sem.__align);
}

void * Producer(void *arg)
{
	printf("\tProducer wait semaphore %d\n",(int)sem.__align);
	sem_post(&sem);
	printf("\tProducer end semaphore %d\n",(int)sem.__align);
}

int main()
{
	pthread_t p1,p2;
	sem_init(&sem,0,0);

	pthread_create(&p1,NULL,Consumer,NULL);
	pthread_create(&p2,NULL,Producer,NULL);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);

	printf("main exit with semaphore %d\n",(int)sem.__align);
	return 0;
}
