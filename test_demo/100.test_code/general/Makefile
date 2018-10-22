OBJS =  test.o file_md5.o md5.o 
CC = gcc  
CFLAGS = -c  
  
all:$(OBJS)  
	$(CC) -o a.out  $(OBJS)  
test:
	$(CC) $(CFLAGS) test.c  
	
file_md5:
	$(CC) $(CFLAGS) file_md5.c  
md5:
	$(CC) $(CFLAGS) md5.c 
 
.PHONY:clean  
clean:  
	rm -rf *.o a.out
	@echo "Clean done!"
