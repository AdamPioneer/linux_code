OBJS =  pipe.o  
CC = gcc  
CFLAGS = -c  
  
all:$(OBJS)  
	$(CC) -o a.out  $(OBJS) -lpthread 
pipe:
	$(CC) $(CFLAGS) pipe.c  -lpthread
	
 
.PHONY:clean  
clean:  
	rm -rf *.o a.out
	@echo "Clean done!"
