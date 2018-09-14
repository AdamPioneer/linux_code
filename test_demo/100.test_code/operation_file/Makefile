OBJS =  test.o crc_8.o  
CC = gcc  
CFLAGS = -c  
  
all:$(OBJS)  
	$(CC) -o test $(OBJS)  
test.o:test.c crc_8.h
	$(CC) $(CFLAGS) test.c  
crc_8.o:crc_8.c crc_8.h
	$(CC) $(CFLAGS) crc_8.c  
  
.PHONY:clean  
clean:  
	rm -rf *.o Test  
	@echo "Clean done!"  




