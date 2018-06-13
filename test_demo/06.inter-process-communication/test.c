/*main.cpp*/


#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <pthread.h>
#include "shm_lib.h"
#include "msg.h"
int main()
{
	int age;
	people *t;


	struct msg_form msg;
	int msqid;
	char c;
	msqid = create_msg();
	printf("msqid = %d \n", msqid);

	while (1) {
		printf("enter one char:");
		scanf("%c", &c);
		if(c == 'q')
			break;
		write_msg(msqid);

	}
	delete_msg(msqid);
	t=initshm();

	//	set_age(t,20);
	//	age = get_age(t);
	printf("%d\n",age);
	return 0;
}
