#include <stdio.h>
#include <stdlib.h>

#include "ecoli_uart_protocol.h"


int main(void)
{
	struct uart_frame frame;
	unsigned char data[MAX_DATA_SIZE] = "0123456789abcdef";
	unsigned char data_len = 16;
	unsigned char frame_id = 0;
	unsigned char frame_type = 0x11;
	unsigned char encode_data[MAX_FRAME_SIZE];
	
	encode_uart_frame(data, data_len, frame_id, frame_type, encode_data);

	printf("-----\n data=%s \n==", data);
	
	for (int i = 0 ; i < data_len+6; i++) {
		
		printf("encode_data[%d]= %d \n", i, encode_data[i]);
	}

	return 0;
}

