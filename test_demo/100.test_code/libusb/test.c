
#include<stdio.h>
//#include<libusb.h>
#include  <libusb-1.0/libusb.h>  
#include<sys/types.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc, char* args[])
{
	int err = 0;
	libusb_context *ctx;
	err = libusb_init(&ctx);
	if (err) {
		fprintf(stderr, "unable to initialize libusb: %i\n", err);
		return EXIT_FAILURE;
	}

	return 0;
}
