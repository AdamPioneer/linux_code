/*****************************************************************************
 *  Copyright          :  All Rights Reserved.
 *
 *  Date               :  2012-09-15 22:37:49
 *  Author/Corporation :  Dengzhaoqun
 *  Email              :  dengzhaoqun@163.com
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "md5.h"
 
char *MD5_file(char *path, char *file_md5, int md5_len)
{
	FILE *fp = fopen (path, "rb");
	MD5_CTX mdContext;
	int bytes;
	unsigned char data[1024];
	
	unsigned char temp_md5[3];  //temporarily save md5 value 
	
	int i;
 
	if (fp == NULL) {
		fprintf (stderr, "fopen %s failed\n", path);
		return NULL;
	}
 
	MD5Init (&mdContext);
	while ((bytes = fread (data, 1, 1024, fp)) != 0)
	{
		MD5Update (&mdContext, data, bytes);
	}
	MD5Final (&mdContext);
	
	if(file_md5 == NULL)
	{
		fprintf(stderr, "malloc failed.\n");
		return NULL;
	}
	
	if(md5_len == 16)
	{
		for(i=4; i<12; i++)
		{
			sprintf(temp_md5, "%02x", mdContext.digest[i]);
			memcpy(&file_md5[(i-4)*2], temp_md5, 2);
			//sprintf(&file_md5[(i-4)*2], "%02x", mdContext.digest[i]);
		}
	}
	else if(md5_len == 32)
	{
		for(i=0; i<16; i++)
		{
			sprintf(temp_md5, "%02x", mdContext.digest[i]);
			memcpy(&file_md5[i*2], temp_md5, 2);
			//sprintf(&file_md5[i*2], "%02x", mdContext.digest[i]);
		}
	}
	else
	{
		fclose(fp);
		return NULL;
	}
	
	fclose(fp);
	return file_md5;
}

#if 0
int main(int argc, char *argv[])
{
	char *md5;
	int md5_len;
	int i = 0;
	
	
	md5_len = 16;
	md5 = (char *)malloc((md5_len + 1) * sizeof(char));
	memset(md5, 0, (md5_len + 1) * sizeof(char));
	for ( i = 0; i < md5_len + 1; i++) {
		printf("md5[%d]=%c\n", i, md5[i]);
	}
	MD5_file("temp",md5, md5_len);
	printf("d16: %s\n", md5);
	for ( i = 0; i < md5_len + 1; i++) {
		printf("md5[%d]=%c\n", i, md5[i]);
	}
	free(md5);

	
	md5_len = 32;
	md5 = (char *)malloc((md5_len + 1) * sizeof(char));
	memset(md5, 0, (md5_len + 1) * sizeof(char));
	MD5_file("temp",md5, md5_len);
	printf("32: %s\n", md5);
	for ( i = 0; i < md5_len; i++) {
		printf("md5[%d]=%c\n", i, md5[i]);
	}
	free(md5);
	return 0;
}
#endif