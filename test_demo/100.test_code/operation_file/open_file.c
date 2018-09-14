#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *arg[])
{
	int ret = 0;
	int fd = 0;
	char buffer[100] = {0};
	fd = open("./log", O_RDONLY);	
	printf("%s:%d:fd=%d, \n",__func__, __LINE__,  fd);
	ret = read(fd, buffer, 1);
	printf("%s:%d:ret=%d, \n",__func__, __LINE__,  ret);
	ret = close(fd);
	printf("%s:%d:ret=%d, \n",__func__, __LINE__,  ret);
	printf("%s:%d:fd=%d, \n",__func__, __LINE__,  fd);
	sleep(20);	
	ret = read(fd, buffer, 1);
	printf("%s:%d:ret=%d, \n",__func__, __LINE__,  ret);
	printf("%s:%d:fd=%d, \n",__func__, __LINE__,  fd);
	return 0;
}
