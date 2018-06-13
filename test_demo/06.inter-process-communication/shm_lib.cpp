/*shm.cpp*/

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <pthread.h>
#include "shm_lib.h"
const char *shmfile="/home/qushenghui/1.txt";
people* initshm(void)
{
	people *p = (people *)Create_sharememory(shmfile,sizeof(people));
	if(p == NULL)
		printf("create sharememory failed!\n");
	return p;
}
void *Create_sharememory(const char *filename,unsigned int SizeCount)
{
	int shm_id,fd;
	key_t key;
	void *pshare;
	const char *path=filename;
	if((fd=open(path,O_RDWR|O_CREAT))<0)
	{
		perror("opne");
		return 0;
	}
	close(fd);
	key=ftok(path,10);
	if(key==-1)
	{
		perror("ftok error\n");
		return 0;
	}
	if((SizeCount%2)!=0)SizeCount++;
	shm_id = shmget(key,SizeCount,IPC_CREAT);
	if(shm_id==-1)
	{
		perror("shmget error\n");
		return 0;
	}
	pshare = shmat(shm_id,NULL,0);
	if(pshare==NULL)
	{
		return 0;
	}
	return pshare;
}
void close_sharememory(void *pshare)
{
	if(shmdt(pshare)==-1)
		perror("detach error");
}
int get_age(people *p)
{
	return p->age;
}
void set_age(people *p,int age)
{
	p->age=age;
}
