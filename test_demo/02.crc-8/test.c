/*
 *test crc-8 program
 */

#include <stdio.h>
#include <stdlib.h>

#include "crc_8.h"
#define OPEN_DEBUG ("open debug")
int main(void)
{
	int ret;
	char tb = 0;
	char lg = 0;
	char ch[] = "abcd";
	char test[] = "open debugdd";
	printf("===================create_crc_table--------\n");
//	create_crc_table();
		
	printf("===================cal_crc_logical --len=%ld------\n", sizeof(ch));
	lg = cal_crc_logical(ch, sizeof(ch));

	printf("===================cal_crc_table --len=%ld------\n", sizeof(ch));
	
	tb = cal_crc_table(ch, sizeof(ch));
	
	printf("----tb=0x%x, lg=0x%x-------\n", tb, lg);
	
	ret = strcmp(test, OPEN_DEBUG);
	printf("strcmp = %d \n", ret);
	return 0;

}


