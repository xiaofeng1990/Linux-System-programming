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
#include <sys/time.h>

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)


void handler(int sig);

int main(int argc, char *argv[])
{
	if(signal(SIGALRM, handler) == SIG_ERR)
		ERR_EXIT("signal error");
	
	struct itimerval it;
	struct timeval tv_interval = {1, 0};
	struct timeval tv_value = {1, 0};
	
	it.it_interval = tv_interval;
	it.it_value = tv_value;
	
	
	setitimer(ITIMER_REAL, &it, NULL);
	
	for(;;)
		pause();
	
	return 0;
}

void handler(int sig)
{
	printf("recv a sig = %d\n", sig);
}