#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>  // shared memory
#include<sys/sem.h>  // semaphore
#include<sys/msg.h>  // message queue
#include<string.h>   // memcpy

// 消息队列结构
struct msg_form {
	long mtype;
	char mtext;
};

int main()
{
	key_t key;
	int shmid, semid, msqid;
	char *shm;
	char data[] = "this is server";
	struct msqid_ds buf2;  /*用于删除消息队列*/
	struct msg_form msg;  /*消息队列用于通知对方更新了共享内存*/

	// 获取key值
	if((key = ftok(".", 'z')) < 0)
	{
		perror("ftok error");
		exit(1);
	}

	// 创建消息队列
	if ((msqid = msgget(key, IPC_CREAT|0777)) == -1)
	{
		perror("msgget error");
		exit(1);
	}

	while(1)
	{
		printf("while\n");
		msgrcv(msqid, &msg, 1, 888, 0); /*读取类型为888的消息*/
		if(msg.mtext == 'q')  /*quit - 跳出循环*/ 
			break;
		if(msg.mtext == 'r')  /*read - 读共享内存*/
		{
			printf("read\n");
		} else {
			printf("else\n");
			sleep(1);
		}
	}


	/*删除共享内存、消息队列、信号量*/
	msgctl(msqid, IPC_RMID, &buf2);
	return 0;
}
