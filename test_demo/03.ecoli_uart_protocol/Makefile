OBJS =  test.o crc_8.o ecoli_uart_protocol.o 
CC = gcc  
CFLAGS = -c  
  
all:$(OBJS)  
	$(CC) -o test $(OBJS)  
test.o:test.c crc_8.h
	$(CC) $(CFLAGS) test.c  
crc_8.o:crc_8.c crc_8.h
	$(CC) $(CFLAGS) crc_8.c  
ecoli_uart_protocol.o:ecoli_uart_protocol.c
	$(CC) $(CFLAGS) ecoli_uart_protocol.c

  
.PHONY:clean  
clean:  
	rm -rf *.o test  
	@echo "Clean done!"  




