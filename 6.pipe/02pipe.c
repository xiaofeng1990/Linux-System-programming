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

//子进程运行ls命令，父进程运行wc命令
//模拟ls | wc -w命令

int main(int argc, char *argv[])
{
	int pipefd[2];
	if(pipe(pipefd) == -1)
		ERR_EXIT("pipe error\n");
	
	pid_t pid;
	pid = fork();
	if(pid == -1)
		ERR_EXIT("fork error\n");
	if(pid == 0)
	{
		/* 将管道的写端口映射到标准输出 ls的输出链接到管道的写*/
		dup2(pipefd[1], STDOUT_FILENO);
		/* 管道的写端口已经映射到标准输出，所以管道的写端口已经没用 */
		close(pipefd[1]);
		
		//
		close(pipefd[0]);
		execlp("ls", "ls", NULL);
		/* 运行到这里说明替换失败 */
		fprintf(stderr, "error execute ls\n");
		exit(EXIT_FAILURE);
	}
	
	/* 将管道的读端口映射到标准输入 */
	dup2(pipefd[0], STDIN_FILENO);
	/* 管道的读端口已经映射到标准输入，所以管道的读端口已经没用 */
	close(pipefd[0]);
	close(pipefd[1]);
	
	/* wc是从标准输入端口读数据 */
	execlp("wc", "wc", "-w", NULL);
	fprintf(stderr, "error execute wc\n");
	exit(EXIT_FAILURE);
	
	
}
