#include "init.h"
#include <signal.h>
#include <stdio.h>
#include "main.h"
#include <string.h>


/****************************************************************************
 * @fn      setup
 *
 * @brief   注册信号
 *
 * @param   None
 *			
 * @return  None
****************************************************************************/
void setup(void)
{
	/* 注册ctrl+c */
	signal(SIGINT, sigint_handler);
	/* 注册ctrl+\,注册行为是忽略该信号 */
	signal(SIGQUIT, SIG_IGN);
}

void sigint_handler(int sig)
{
	printf("\n[minishell]$ ");
	fflush(stdout);
}

void init(void)
{
	int i;
	
	memset(cmd, 0, sizeof(cmd));
	for(i = 0; i<PIPELINE; i++)
	{
		cmd[i].infd = 0;
		cmd[i].outfd = 1;
	}
	memset(cmdline, 0, sizeof(cmdline));
	memset(avline, 0, sizeof(avline));

	memset(infile, 0, sizeof(infile));
	memset(outfile, 0, sizeof(outfile));
	lineptr = cmdline;	/* 指向 lineptr */
	avptr   = avline;	/* 指向 avline */
	
	cmd_count = 0;				/* 命令个数 */
	backgnd = 0;				/* 是否后台运行 */
	append = 0;						
	lastpid = 0;
}
