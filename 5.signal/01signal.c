#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>


#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)


void handler(int sig);

int main(int argc, char *argv[])
{
	if(signal(SIGINT, handler) == SIG_ERR)
		ERR_EXIT("signal error");
	for (;;);
	
	return 0;
}

void handler(int sig)
{
	printf("recv a sig = %d\n", sig);
}