#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<signal.h>

//定义消息结构体
typedef struct msgbuf
{
	long channel;//消息结构体的第一个元素必须是long类型
	char buf[256];
}msg_t;

int msgid = -1;

//信号处理函数
void handler(int s)
{
	//int msgctl(int msqid, int cmd, structmsqid_ds *buf);
	//参数1：调用msgget函数返回的消息队列号
	//参数2：执行的操作类型
	//参数3：接收消息队列的信息

	printf("%s:%d\n", __func__, __LINE__);
	if (msgid == -1)
		return ;

	msgctl(msgid, IPC_RMID, 0);
	fprintf(stdout, "exit\n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	if (argc < 2) 
		fprintf(stderr,"usage:%s msgid\n", argv[0]), exit(EXIT_FAILURE);

	//注册中断信号
	signal(SIGINT, handler);



	//创建消息队列  int msgget(key_t key, int msgflg);
	//参数1：消息队列的key值(标识一个消息队列)
	//参数2：如果key对应的消息队列不存在则创建之，如果存在则打开

	msgid = msgget(atoi(argv[1]), 0);
	if (-1 == msgid)
		perror("msgget"), exit(EXIT_FAILURE);
	//定义并初始化消息结构体
	msg_t msg;
	memset(&msg, 0x00, sizeof(msg));

	while (1)
	{
		//输入要接收的频道数（消息类别编号）
		printf("channel:");
		scanf("%d",&msg.channel);
		//int msgsnd(int msqid, const void*msgp, size_t msgsz, int msgflg);
		//参数1：调用msgget函数返回的消息队列号
		//参数2：待接收的消息结构体地址
		//参数3：待接收的消息长度（不包括消息结构体的第一个元素）
		//参数4：接受的channel号
		//参数5：附加功能（没有特殊需求填0即可）
		msgrcv(msgid, &msg,sizeof(msg.buf), msg.channel, 0);
		fprintf(stdout, "msg: %s\n",msg.buf);
	}

	return 0;
}

//--------------------- 
//作者：tf_apologize 
//来源：CSDN 
//原文：https://blog.csdn.net/tf_apologize/article/details/70194480 
//版权声明：本文为博主原创文章，转载请附上博文链接！
