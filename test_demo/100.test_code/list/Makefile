OBJS =  test.o  
CC = gcc  
CFLAGS = -c  
  
all:$(OBJS)  
	$(CC) -o a.out  $(OBJS)  
test:
	$(CC) $(CFLAGS) test.c  
	
 
.PHONY:clean  
clean:  
	rm -rf *.o a.out
	@echo "Clean done!"
