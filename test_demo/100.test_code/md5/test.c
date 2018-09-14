#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_md5.h"

int main(int argc, char *argv[])
{
	char *md5;
	int md5_len;
	int i = 0;
	
	
	md5_len = 16;
	md5 = (char *)malloc((md5_len + 1) * sizeof(char));
	memset(md5, 0, (md5_len + 1) * sizeof(char));
	MD5_file("temp",md5, md5_len);
	printf("d16: %s\n", md5);

	free(md5);

	
	md5_len = 32;
	md5 = (char *)malloc((md5_len + 1) * sizeof(char));
	memset(md5, 0, (md5_len + 1) * sizeof(char));
	MD5_file("temp",md5, md5_len);
	printf("32: %s\n", md5);

	free(md5);
	return 0;
}
