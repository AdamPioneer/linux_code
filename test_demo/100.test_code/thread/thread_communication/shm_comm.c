#include "shm_comm.h"

static int commShmid(int size,int flag)
{
    key_t key=ftok(PATHNAME,PROJ_ID);
    if(key>0)
    {   
        return shmget(5555,size,flag);
    }   
    else
    {   
        perror("ftok");
        return -1; 
    }   
}
 
int CreatShmid(int size)
{
    return commShmid(size,IPC_CREAT|IPC_EXCL|0666);
 //  return commShmid(size,IPC_CREAT|0666);
}
int GetShmid(int size)
{
    return commShmid(size,IPC_CREAT);
}
int Destory(int shmid)
{
    return shmctl(shmid,0,IPC_RMID);
}
/*
--------------------- 
作者：sky_Mata 
来源：CSDN 
原文：https://blog.csdn.net/skyroben/article/details/72625028 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/
