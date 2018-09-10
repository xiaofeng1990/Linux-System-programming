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
	struct sigaction act;
	
	/* 注册信号处理函数 */
	act.sa_handler = handler;
	
	/* 清空信号位 */
	sigemptyset(&act.sa_mask);
	
	/**/
	act.sa_flags = 0;
	
	if(sigaction(SIGINT, &act, NULL) < 0)
		ERR_EXIT("sigaction error");
	
	for(;;)
		pause();	//将进程置为睡眠，直到接收一个信号
	return 0;
}

void handler(int sig)
{
	printf("recv a sig=%d\n", sig);
}
