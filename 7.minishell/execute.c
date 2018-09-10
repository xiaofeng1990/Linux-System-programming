#include "parse.h"
#include <stdio.h>
#include "main.h"
#include "init.h"


#include "def.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "execute.h"


/****************************************************************************
 * @fn		execute_command
 *
 * @brief	执行命令
 *
 * @param	None
 *			
 * @return	succeed：the numbers of command	 error: -1
****************************************************************************/
int execute_disk_command(void)
{

	/* ls | grep init | wc -w */
	int i;
	int fds[2];
	int fd;

	if(cmd_count == 0)
		return 0;

	
	if(infile[0] != '\0')
		cmd[0].infd = open(infile, O_RDONLY);
	if(outfile[0] != '\0')
	{
		if(append)
			/* 追加方式打开 */
			cmd[cmd_count - 1].outfd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			/* 清空方式打开 */
			cmd[cmd_count - 1].outfd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			
	}

	/* 后台作业防止僵尸进程的出现，当子进程退出后，
	   会给父进程发一个 SIGCHLD的信号，该注册行为 SIG_IGN 忽略该信号*/
	if(backgnd == 1)
		signal(SIGCHLD, SIG_IGN);
	else
		/* 因为前台作业需要等待子进程的退出，所以当backgnd=0的时候需要将SIGCHLD信号重新关联为默认 */
		signal(SIGCHLD, SIG_DFL);	
	
	for(i = 0; i<cmd_count; ++i)
	{
		/* 如果不是最后一条命令，这需要创建管道 */
		if(i<cmd_count -1)
		{
			pipe(fds);
			/* 当前命令的输出映射到管道的写端口 */
			cmd[i].outfd = fds[1];
			/* 下一条命令的输入映射到管道的读端口 */
			cmd[i+1].infd = fds[0];
		}
		forkexec(i);

		/* 能运行到这里，是父进程返回，子进程运行命令 */
		if((fd = cmd[i].infd) != 0)
			close(fd);
		if((fd = cmd[i].outfd) != 1)
			close(fd);
		
	}
	
	/* 前台作业，等待管道中最后一个子进程退出*/
	if(backgnd == 0)
		while(wait(NULL) != lastpid);
		
	return 0;
}

void forkexec(int i)
{
	pid_t pid;
	int j;
	pid = fork();
	if(pid == -1)
		ERR_EXIT("fork error\n");
	if(pid > 0)
	{
		/* 父进程 */
		if(backgnd == 1)
			printf("%d\n", pid);
		
		lastpid = pid;	//子进程pid
	}

	else if(pid == 0)
	{
		/* 当backgnd = 1时，将第一条简单命令的infd重定向到/dev/null */
		/* 当地一条命令试图从标准输入获取数据的时候立即返回EOF */
		if(cmd[i].infd == '\0'&& backgnd == 1)
			cmd[i].infd = open("/dev/null", O_RDONLY);
		
		/* 将第一个简单命令进程作为进程组组长 */
		if(i == 0)
			setpgid(0, 0);
		/* 子进程 */
		if(cmd[i].infd != 0)		//可能是管道的读端口
		{
			close(0);
			dup(cmd[i].infd);	//将关闭的标准输入映射到管道的读
		}
		if(cmd[i].outfd != 1)
		{
			close(1);
			dup(cmd[i].outfd);	//将关闭的标准输出映射到管道的写端口
		}
		
		for(j = 3; j < open_max; ++j)
			close(j);

		if(backgnd == 0)
		{
			/* 如果是前台作业，ctrl+c 和ctrl+/重新关联为默认动作，应为推出前台作业子进程，返回父进程 */
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
		}
		execvp(cmd[i].args[0], cmd[i].args);

		/* 如果替换成功，不会运行到这里 */
		exit(EXIT_FAILURE);
	}
}



