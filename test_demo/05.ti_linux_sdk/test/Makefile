# test program
TARGET = hello_world
OBJS =  hello_world.o
#CC = gcc  
CC = /home/ti_linux/ti-processor-sdk-linux-am57xx-evm-04.02.00.09/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf-gcc
CFLAGS = -c  
  
all:$(OBJS)  
	$(CC) -o $(TARGET) $(OBJS)  
test.o:hello_world.c
	$(CC) $(CFLAGS) hello_world.c  

crc_8.o:crc_8.c crc_8.h
	$(CC) $(CFLAGS) crc_8.c  
  
.PHONY:clean  
clean:  
	rm -rf *.o Test  
	@echo "Clean done!"  




