all : server client msg_server msg_client
CFLAGS = -c -Wall

shm_server.o : shm_server.c
shm_client.o : shm_client.c
msg_server.o : msg_server.c
msg_client.o : msg_client.c




server : shm_server.o
	cc -pthread -o server shm_server.o

client : shm_client.o
	cc -pthread -o client shm_client.o

msg_server : msg_server.o
	cc -pthread -o msg_server msg_server.o

msg_client : msg_client.o
	cc -pthread -o msg_client msg_client.o




.PHONY : clean
clean :
	rm msg_client
	rm msg_server
	rm client
	rm server
	rm *.o

