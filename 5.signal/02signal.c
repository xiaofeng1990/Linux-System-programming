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
	__sighandler_t oldhandler;
	
	/* 返回上次安装的handler */
	oldhandler = signal(SIGINT, handler);
	if(oldhandler == SIG_ERR)
		ERR_EXIT("signal error");
	
	while(getchar() != '\n');
	/* 
	if (signal(SIGINT, oldhandler) == SIG_ERR)
	*/
    /* 关联为默认处理程序 */
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		ERR_EXIT("signal error");
	for (;;);
	
	return 0;
}

void handler(int sig)
{
	printf("recv a sig = %d\n", sig);
}