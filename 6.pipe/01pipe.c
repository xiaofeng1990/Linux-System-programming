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

//子进程通过管道发送数据，父进程通过管道读取数据
//子进程继承父进程的管道

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
		/* 子进程关闭管道的读端口 */
		close(pipefd[0]);
		write(pipefd[1], "hello", 5);
		
		/* 写完关闭管道写端口 */
		close(pipefd[1]);
		
		/* 退出子进程 */
		exit(EXIT_FAILURE);
	}
	
	/* 运行都这里说明是父进程 */
	/* 父进程关闭读端口 */
	close(pipefd[1]);
	
	char buf[10];
	
	//fcntl(pipefd[0], F_SETFL, flags | O_NONBLOCK);	//将文件描述符添加非阻塞属性，这样管道读会返回错误
	read(pipefd[0], buf, 10);
	
	printf("buf = %s\n", buf);
	
	return 0;
	
}
