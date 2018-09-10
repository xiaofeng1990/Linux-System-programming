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

/* waitpid and wait 等待子进程推出 */
		
int main(int argc, char *argv[])
{
	pid_t pid;
	int status;
	int ret;
	
	pid = fork();
	if(pid == -1)
	{
		ERR_EXIT("fork error");
	}
	if(pid == 0)
	{
		sleep(3);
		printf("this is child\n");
		/* 推出子进程 */
		//exit(100);
		/* 异常终止 */
		abort();
	}
	
	/* 运行到这里一定是父进程 */
	
	printf("this is parent\n");
	/* 等待子进程退出，防止僵尸子进程 返回值为退出子进程*/
	
	/* 等待任意一个子进程退出 */
	//ret = wait(&status);
	//ret = waitpid(-1, &status, 0);
	/* 上面两个等价 */
	
	
	/* 等待特定子进程退出 */
	ret = waitpid(pid, &status, 0);
	printf("ret = %d pid = %d\n", ret, pid);
	
	/* 子进程正常退出 WEXITSTATUS捕获正常退出信号*/
	if(WIFEXITED(status))
		printf("child exited normal exit status = %d\n", WEXITSTATUS(status));
	/*else
		printf("child exited abnormal exit\n");
	*/
	/* 子进程因捕获信号而终止 */
	else if(WIFSIGNALED(status))
		printf("child exited abnormal exit signal number=%d\n", WTERMSIG(status));
	
	/* 父进程捕获到子进程暂停信号而终止 */
	else if (WIFSTOPPED(status))
		printf("child stoped signal number=%d\n", WSTOPSIG(status));
	return 0;
}