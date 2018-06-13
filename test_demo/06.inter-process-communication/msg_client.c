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
	struct msg_form msg;
	int flag = 1; /*while循环条件*/

	// 获取key值
	if((key = ftok(".", 'z')) < 0)
	{
		perror("ftok error");
		exit(1);
	}

	// 创建消息队列
	if ((msqid = msgget(key, 0)) == -1)
	{
		perror("msgget error");
		exit(1);
	}


	// 写数据
	printf("***************************************\n");
	printf("*                 IPC                 *\n");
	printf("*    Input r to send data to server.  *\n");
	printf("*    Input q to quit.                 *\n");
	printf("***************************************\n");

	while(flag)
	{
		char c;
		printf("Please input command: ");
		scanf("%c", &c);
		switch(c)
		{
			case 'r':
				printf("Data to send: ");
				/*清空标准输入缓冲区*/
				while((c=getchar())!='\n' && c!=EOF);
				msg.mtype = 888;  
				msg.mtext = 'r';  /*发送消息通知服务器读数据*/
				msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
				break;
			case 'q':
				msg.mtype = 888;
				msg.mtext = 'q';
				msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
				flag = 0;
				break;
			default:
				printf("Wrong input!\n");
				/*清空标准输入缓冲区*/
				while((c=getchar())!='\n' && c!=EOF);
		}
	}

	return 0;
}
