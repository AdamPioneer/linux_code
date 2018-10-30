#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>


void *thread_func(void *msg);
sem_t sem;

#define MSG_SIZE 512


int main(int argc, char *argv[])
{
	int i = 0;
	int res = -1;
	pthread_t thread;
	void *thread_result = NULL;
	char msg[MSG_SIZE] = {0};

	res = sem_init(&sem, 0, 0);
	if (res != 0)
	{
		perror("semaphore initializtion failed!\n");
		exit(EXIT_FAILURE);
	}
	
	res = pthread_create(&thread, NULL, thread_func, msg);
	if (res != 0)
	{
		perror("pthread create failed!\n");
		exit(EXIT_FAILURE);
	}

	printf("input some text, Enter 'end' to finish.....\n");

	while(strcmp("end\n", msg) != 0)
	{
		fgets(msg, MSG_SIZE, stdin);
		sem_post(&sem);
	}

	printf("waiting for thread to finish .. \n");

	res = pthread_join(thread, &thread_result);
	if (res != 0)
	{
		perror("join failed!\n");
		exit(EXIT_FAILURE);
	}

	printf("thead joined\n");
	sem_destroy(&sem);
	exit(EXIT_SUCCESS);
	return 0;
}


void *thread_func(void *msg)
{
	printf("child thread begin\n");
 
	sem_wait(&sem);
	printf("wait  begin\n");
	char *ptr = msg;
	while(strcmp("end\n", msg) != 0)
	{
		int i = 0;
		//把小写字母变成大写
		for(; ptr[i] != '\0'; ++i)
		{
			if(ptr[i] >= 'a' && ptr[i] <= 'z')
			{
				ptr[i] -= 'a' - 'A';
			}
		}
		printf("You input %d characters\n", i-1);
		printf("To Uppercase: %s\n", ptr);
		//把信号量减1
		sem_wait(&sem);
	}
	//退出线程
	pthread_exit(NULL);

}

