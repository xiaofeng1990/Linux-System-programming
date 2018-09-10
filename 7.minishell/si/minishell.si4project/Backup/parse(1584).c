#include "parse.h"
#include <stdio.h>
#include "main.h"
#include "init.h"
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/****************************************************************************
 * @fn      shell_loop
 *
 * @brief   shell主循环
 *
 * @param   None
 *			
 * @return  None
****************************************************************************/
void shell_loop(void)
{
	while (1)
	{
		printf("[minishell]$ ");
		fflush(stdout);
		init();
		if (read_command() == -1)
			break;
		parse_command();
		execute_command();
	}
	
	printf("\nexit\n");
	
}


/****************************************************************************
 * @fn      read_command
 *
 * @brief   读取命令
 *
 * @param   None
 *			
 * @return  succeed：0	other：-1
****************************************************************************/
int read_command(void)
{
	if (fgets(cmdline, MAXLINE, stdin) == NULL)
		return -1;
	return 0;
}



/****************************************************************************
 * @fn		parse_command
 *
 * @brief	解析命令
 *
 * @param	None
 *			
 * @return	succeed：the numbers of command 	 error: -1
****************************************************************************/
int parse_command(void)
{
	/* ls -l --> ls\0-l\0 */
	char *cp = cmdline;
	char *avp = avline;
	int i = 0;
	
	while(*cp != '\0')
	{
		/* 过滤空格 */
		while(*cp == ' ' || *cp == '\t')
			cp++;
		/* 如果到达行尾，表示输入为空命令，跳出循环 */
		if(*cp == '\0' || *cp == '\n')
			break;
		cmd.args[i] = avp;
		/* 解析参数 */
		while (*cp != '\0' && *cp != ' '&& *cp != '\t'&& *cp != '\n')
			*avp++ = *cp++;
		*avp++ = '\0';
		printf("[%s]\n", cmd.args[i]);
		i++;
	}
	return 0;
}


/****************************************************************************
 * @fn		execute_command
 *
 * @brief	执行命令
 *
 * @param	None
 *			
 * @return	succeed：the numbers of command	 error: -1
****************************************************************************/
int execute_command(void)
{
	int ret = 0;
	pid_t pid = fork();
	if (pid == -1)
		ERR_EXIT("fork error");
	
	if(pid == 0)
		execvp(cmd.args[0], cmd.args);

	wait(NULL);
	
	return 0;
}


