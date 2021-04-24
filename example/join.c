#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void    *routine(void *arg)
{
	pthread_t tid;

	tid = pthread_self();
	printf("\ttid: %x\n", tid);
	int i = 0;
	while (i < 10)
	{
		printf("\tnew thread: %d\n", i);
		i++;
		usleep(2);
	}
}

int     main()
{
	pthread_t thread;
	pthread_create(&thread, NULL, routine, NULL);
	int i = 0 ;
	printf("tid: %x\n", pthread_self());
	while (i < 5)
	{
		printf("main:%d\n", i);
		i++;
		usleep(2);
	}
	pthread_join(thread, NULL);
}