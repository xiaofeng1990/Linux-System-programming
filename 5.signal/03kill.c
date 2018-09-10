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
	if (signal(SIGUSR1, handler) == SIG_ERR)
		ERR_EXIT("signal error");
	pid_t pid = fork();
	if (pid == -1)
		ERR_EXIT("fork error");

	if (pid == 0)
	{
		/* 向父进程发送9号信号 */
		//kill(getppid(), SIGUSR1);
		
		/* 向进程组发送 */
		/*pid = getpgrp();
		kill(-pid, SIGUSR1);*/
		
		killpg(getpgrp(), SIGUSR1);
		exit(EXIT_SUCCESS);
	}

	int n = 5;
	
	/* 如果被信号终端，返回剩余时间，然后循环添加剩余时间 */
	do
	{
		n = sleep(n);
	} while (n > 0);
	return 0;
}

void handler(int sig)
{
	printf("recv a sig=%d\n", sig);
}
