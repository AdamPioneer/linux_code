#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_md5.h"

int main(int argc, char *argv[])
{
	int ar_1[] = {0,0,};	
	int ar_2[] = {0,0};	
	int ar_3[2] = {0,0,};	
	int ar_4[2] = {0,0};
	printf("%d:%d:%d:%d\n", sizeof(ar_1)/sizeof(int), sizeof(ar_2)/sizeof(int),sizeof(ar_3)/sizeof(int),sizeof(ar_4)/sizeof(int));
	
	return 0;
}
