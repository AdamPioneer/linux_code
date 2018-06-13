#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>  // shared memory
#include<sys/sem.h>  // semaphore
#include<sys/msg.h>  // message queue
#include<string.h>   // memcpy

#include "msg.h"
int create_msg(void)
{
	key_t key;
        int msqid;
	       
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
	
	return msqid;
}

int read_msg(int msqid, struct msg_form *msg)
{
	msgrcv(msqid, msg, 1, 888, 0); /*读取类型为888的消息*/
	printf("read data mtext: %c \n", msg->mtext);
	return 0;
}

//int write_msg(int msqid, struct msg_form *msg)
int write_msg(int msqid)
{
	struct msg_form msg;
	msg.mtype = 888;  
	msg.mtext = 'r';  /*发送消息通知服务器读数据*/
	msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
	return 0;
}

int delete_msg(int msqid)
{
	struct msqid_ds buf2;  /*用于删除消息队列*/
	msgctl(msqid, IPC_RMID, &buf2);
	return 0;
}

