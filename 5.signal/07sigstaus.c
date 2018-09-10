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
void printsigset(sigset_t *set)
{
	int i;
	for(i = 0; i<NSIG; i++)
	{
		/* 检测信号集相应位是否为1 */
		if(sigismember(set, i))
			putchar('1');
		else
			putchar('0');
	}
	printf("\n");
	
}

int main(int argc, char *argv[])
{
	sigset_t pset;
	sigset_t bset;
	
	/* 将信号变量都置为0 */
	sigemptyset(&bset);
	/* 添加要阻塞的信号 */
	sigaddset(&bset, SIGINT);
	/* 注册信号处理函数 */
	if (signal(SIGINT, handler) == SIG_ERR)
		ERR_EXIT("signal error");
	if (signal(SIGQUIT, handler) == SIG_ERR)
		ERR_EXIT("signal error");
	
	/* 将相应信号为未决，不抵达 将信号阻塞 */
	sigprocmask(SIG_BLOCK, &bset, NULL);
	
	for (;;)
	{
		/* 获取未决信号 */
		sigpending(&pset);
		printsigset(&pset);
		sleep(2);
	}
	return 0;
}

void handler(int sig)
{
	if(sig == SIGINT)
		printf("recv a sig=%d\n", sig);
	else if(sig == SIGQUIT)
	{
		sigset_t uset;
		/* 清空标志 */
		sigemptyset(&uset);
		/* 添加信号 */
		sigaddset(&uset, SIGINT);
		/* 将信号解除阻塞 */
		sigprocmask(SIG_UNBLOCK, &uset, NULL);
		
	}
	/* 一秒后重新发送信号 */
}
