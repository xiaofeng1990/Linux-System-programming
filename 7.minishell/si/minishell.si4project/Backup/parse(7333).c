#include "parse.h"
#include <stdio.h>

/***************************************************************************************************
 * @fn      shell_loop
 *
 * @brief   shell主循环
 *
 * @param   None
 *			
 * @return  None
***************************************************************************************************/
void shell_loop(void)
{
	while (1)
	{
		printf("[minishell]$ ");

		/* 清除缓冲区数据集流 */
		fflush(stdout);
		if(read_command() == -1)
			break;
		
		parse_command();
		execute_command();
	}

	printf("\nexit\n");
	
}


/***************************************************************************************************
 * @fn      read_command
 *
 * @brief   读取命令
 *
 * @param   None
 *			
 * @return  succeed：0	other：-1
***************************************************************************************************/
int read_command(void)
{
	fgets
	return 0;
}



/***************************************************************************************************
 * @fn		parse_command
 *
 * @brief	解析命令
 *
 * @param	None
 *			
 * @return	succeed：the numbers of command 	 error: -1
***************************************************************************************************/
int parse_command(void)
{
	return 0;
}


/***************************************************************************************************
 * @fn		execute_command
 *
 * @brief	执行命令
 *
 * @param	None
 *			
 * @return	succeed：the numbers of command	 error: -1
***************************************************************************************************/
int execute_command(void)
{
	return 0;
}


