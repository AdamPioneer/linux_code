#ifndef _ECOLI_UART_PROTOCOL_H
#define _ECOLI_UART_PROTOCOL_H

/*
 *|-START-|--UID--|--TYPE-|--LEN--|-MAX 128BYTE-|--CRC--|--END--|
 *|-8BITS-|-8BITS-|-8BITS-|-8BITS-|-MAX 128BYTE-|-8BITS-|-8BITS-|
 * START=0XDB
 * END=0XB0
 * CRC IS CRC8
 * 
 */

#define START_FLAG      0xDB
#define END_FLAG        0xB0
#define END2_FLAG       0xB1

#define START_FLAG_SIZE 1
#define FRMAE_ID_SIZE 1
#define FRAME_TYPE_SIZE 1
#define FRAME_LEN_SIZE 1
#define FRMAE_CRC_SIZE 1
#define NED_FLAG_SIZE 1

#define START_FLAG_OFFSET 0
#define FRAME_ID_OFFSET         START_FLAG_OFFSET + START_FLAG_SIZE
#define FRAME_TYPE_OFFSET       FRAME_ID_OFFSET + FRMAE_ID_SIZE
#define FRAME_LEN_OFFSET        FRAME_TYPE_OFFSET + FRAME_TYPE_SIZE
#define FRAME_DATA_OFFSET       FRAME_LEN_OFFSET + FRAME_LEN_SIZE

#define MAX_DATA_SIZE 128
#define MAX_FRAME_SIZE MAX_DATA_SIZE + 6

enum ecoli_type {
	/* frame type */
	ECOLI_ACK = 0x00,
	ECOLI_CMD = 0x01,
	ECOLI_DATA = 0x02,
	ECOLI_HEART = 0x03,

	/* frame target */
	ECOLI_PUMP = 0x10,
	ECOLI_VALVE = 0x20,
	ECOLI_TEMP = 0x30,

	ECOLI_UNKNOWN = 0xFF,	
};

struct uart_frame {
        unsigned char start; /* start char, 8bits*/
        unsigned char frame_id; /* indicate frame number, 8bits*/
        unsigned char type;    /* low 4bits is data type, high 4bits is target */
        unsigned char len;     /* data length*/
	void *data;        /* data, max length is 128byte */
        unsigned char crc; /* crc-8 */
        unsigned char /* end char, 8bits*/
};


unsigned char *encode_uart_frame(const char *data, unsigned char data_len,
        unsigned char frame_id, unsigned char frame_type, unsigned char *encode_frame);

#endif /*_ECOLI_UART_PROTOCOL_H*/
