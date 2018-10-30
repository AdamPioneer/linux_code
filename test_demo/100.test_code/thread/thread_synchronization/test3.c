#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
	char message = 'X';
	int i = 0;	
	if(argc > 1)
		message = argv[1][0];
	for(i = 0; i < 10; ++i)
	{
		printf("%c", message);
		fflush(stdout);
		sleep(rand() % 3);
		printf("%c", message);
		fflush(stdout);
		sleep(rand() % 2);
	}
	sleep(10);
	printf("\n%d - finished\n", getpid());
	exit(EXIT_SUCCESS);
}
--------------------- 
作者：ljianhui 
来源：CSDN 
原文：https://blog.csdn.net/ljianhui/article/details/10243617 
版权声明：本文为博主原创文章，转载请附上博文链接！
