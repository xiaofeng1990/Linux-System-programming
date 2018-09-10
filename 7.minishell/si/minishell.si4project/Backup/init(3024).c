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
	memset(&cmd, 0, sizeof(struct command));
	memset(cmdline, 0, sizeof(cmdline));
	
}
