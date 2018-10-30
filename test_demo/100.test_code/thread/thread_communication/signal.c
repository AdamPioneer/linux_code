/*************************************************************************
	> File Name: signal.c
	> Author: 
	> Mail: 
	> Created Time: Sun 29 Jul 2018 04:02:53 PM CST
 ************************************************************************/
 
#include<stdio.h>
#include <unistd.h>
#include <signal.h>
 
//自定义信号处理程序
int myhandle(int num)
{
    printf("myhandle running..\n");
    printf("signal num is = %d \n",num);
 
    //解除阻塞
    if(num==SIGUSR1)
    {
        //解除阻塞非实时信号和实时信号
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set,SIGINT);
        sigaddset(&set,SIGRTMIN);
        sigprocmask(SIG_UNBLOCK,&set,NULL);
        printf("收到自定义信号,解除阻塞：%d\n",num);
    }
    if(num==SIGINT)
    {
        printf("收到非实时信号：%d\n",num);
    }
    if(num==SIGRTMIN)
    {
        printf("收到实时信号：%d\n",num);
    }
}
 
int main()
{
    pid_t  pid;
 
    int ret = 0;
 
    struct sigaction act;
    act.sa_handler = myhandle;
    //act.sa_flags = SA_SIGINFO;
 
    //注册非实时信号
    if(sigaction(SIGINT,&act,NULL)<0)
    {
        perror("sigaction err:");
        exit(-1);
    }
 
    //注册实时信号 kill -l 显示所有信号
    if(sigaction(SIGRTMIN,&act,NULL)<0)
    {
        perror("sigaction err:");
        exit(-1);
    }
 
    //注册用户自定义信号
    if(sigaction(SIGUSR1,&act,NULL)<0)
    {
        perror("sigaction err:");
        exit(-1);
    }
 
    //阻塞非实时信号和实时信号
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    sigaddset(&set,SIGRTMIN);
    sigprocmask(SIG_BLOCK,&set,NULL);
 
    pid =  fork();
    if(pid==0)
    {
        //子进程向父进程发送信号
        printf("子进程发送信号\n");
        union sigval value;
        //参数是子进程的pid
        value.sival_int = getpid();
        int i=0;
        for(i=0;i<3;++i)
        {
            //发送3次非实时信号
            if(sigqueue(getppid(),SIGINT,value)<0)
            {
                perror("sigqueue SIGINT error:");
                exit(-3);
            }
            printf("发送非实时信号\n");
        }
       for(i=0;i<3;++i)
        {
            //发送3次实时信号
            if(sigqueue(getppid(),SIGRTMIN,value)<0)
            {
                perror("sigqueue SIGINT error:");
                exit(-3);
            }
            printf("发送实时信号\n");
        }
        //发送自定义信号解除阻塞,kill同sigqueue
        kill(getppid(),SIGUSR1);
    }
    else if(pid > 0)
    {
        //父进程
        while(1)
        {
            sleep(1);
        }
    }
    else
    {
        //error
        perror("fork error:");
        exit(-2);
    }
 
    return 0;
}
/*
--------------------- 
作者：江山美人1 
来源：CSDN 
原文：https://blog.csdn.net/u011285208/article/details/82503611 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/
