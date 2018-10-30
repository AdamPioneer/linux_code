#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>

//定义消息结构体

typedef struct msgbuf
{
	long channel;//消息结构体的第一个元素必须是long类型(消息类别号)
	char buf[256];//保存消息（消息体）
}msg_t;

int main(int argc, char **argv)
{
	if (argc < 2)
		fprintf(stderr,"usage:%s msgid\n", argv[0]), exit(1);
	//创建消息队列  int msgget(key_t key, int msgflg);
	//参数1：消息队列的key值(标识一个消息队列)
	//参数2：如果key对应的消息队列不存在则创建之，如果存在则打开
	int msgid = msgget(atoi(argv[1]), IPC_CREAT| IPC_EXCL | 0666);
	if (-1 == msgid)
		perror("msgget"), exit(1);

	//定义并初始化消息结构体
	msg_t msg;
	memset(&msg, 0x00, sizeof(msg));
	while (1) {
		//输入通道号（消息类别）
		printf("channel:");
		scanf("%d",&msg.channel);
		scanf("%*c");//读取缓冲区中的换行符
		//从标准输入获取数据，以回车结束

		printf("msg:");

		fgets(msg.buf, sizeof(msg.buf), stdin);

		//scanf("%*c");//由于fgets会接收\n,不用再接收换行符

		//int msgsnd(int msqid, const void*msgp, size_t msgsz, int msgflg);

		//参数1：调用msgget函数返回的消息队列号（标识符）
		//参数2：待发送的消息结构体地址
		//参数3：待发送的消息长度（不包括消息结构体的第一个元素）
		//参数4：附加功能（没有特殊需求填0即可）
		msgsnd(msgid, &msg,sizeof(msg.buf), 0);

		char ch = ' ';

		fprintf(stdout, "是否继续发送？[yn]:");
		scanf("%[yYnN]", &ch);
		scanf("%*c");

		if ('y' != ch && 'Y' != ch)
		{
			break;
		}
	}

	//int msgctl(int msqid, int cmd, structmsqid_ds *buf);
	//参数1：调用msgget函数返回的消息队列号
	//参数2：执行的操作类型
	//参数3：消息队列状态信息结构体指针
	msgctl(msgid, IPC_RMID, 0);

	return 0;

}
//作者：tf_apologize 
//来源：CSDN 
//原文：https://blog.csdn.net/tf_apologize/article/details/70194480 
//版权声明：本文为博主原创文章，转载请附上博文链接！
