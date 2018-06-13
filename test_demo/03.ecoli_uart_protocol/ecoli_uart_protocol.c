/*
 * File Name          : ecoli_uart_protocol.c
 * Description        : ecoli uart communication protocol
 * COPYRIGHT(c) 2017 BGI
 */

#include <string.h>
#include "ecoli_uart_protocol.h"
#include "crc_8.h"

unsigned char *encode_uart_frame(const char *data, unsigned char data_len, 
	unsigned char frame_id, unsigned char frame_type, unsigned char *encode_frame)
{
	int crc_offset = FRAME_DATA_OFFSET + data_len;
	int crc_len = FRMAE_ID_SIZE + FRAME_TYPE_SIZE + FRAME_LEN_SIZE + data_len;
	unsigned char *data_start = encode_frame + FRAME_DATA_OFFSET;
	
	encode_frame[START_FLAG_OFFSET] = START_FLAG;
	encode_frame[FRAME_ID_OFFSET] = frame_id;
	encode_frame[FRAME_TYPE_OFFSET] = frame_type;
	encode_frame[FRAME_LEN_OFFSET] = data_len;
	memcpy(data_start, data, data_len);
	
	encode_frame[crc_offset] = cal_crc_table(encode_frame + FRAME_ID_OFFSET, crc_len);
	
	encode_frame[crc_offset + 1] = END_FLAG;
	
	return encode_frame;
}


unsigned char decode_frame_id(const char *data)
{
	return data[FRAME_ID_OFFSET];
}

unsigned char decode_frame_data_type(const char *data)
{
	
	return data[FRAME_TYPE_OFFSET] & 0x0F;
}



unsigned char decode_frame_data_target(const char *data)
{

	return data[FRAME_TYPE_OFFSET] & 0xF0;
}

unsigned char decode_frame_data_len(const char *data)
{
}
