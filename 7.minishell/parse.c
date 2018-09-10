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

#include "builtin.h"



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
		init();
		if (read_command() == -1)
			break;
		parse_command();
		//print_command();
		execute_command();
	}
	
	printf("\n exit\n");
	
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
	if(check("\n"))
		return 0;

	/* 判断是否是内部命令 并执行*/
	if(builtin())
		return 0;
	
	/* cat < test.txt |grep -n public > test2.txt & */
	/* 1.解析第一条简单命令 */
	get_command(0);
	/* 2.判定是否有输入重定向符 */
	if(check("<"))
		getname(infile);
	
	/* 3.判断是否有管道 */
	int i;
	for(i=1; i<PIPELINE; ++i)
	{
		if(check("|"))
			get_command(i);
		else
			break;
		
	}
	/* 4.判定是否有输出重定向符 */
	if(check(">"))
	{
		if(check(">"))
			append = 1;
		getname(outfile);
	}
		
	
	/* 5.判定是否有后台作业 */
	if(check("&"))
		backgnd = 1;
	
	/* 6.判定命令结束      '\n' */
	if(check("\n"))
	{
		cmd_count = i;
		return cmd_count;
	}
	else
	{
		fprintf(stderr, "Command line syntax error\n");
		return -1;
	}
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

	/* 新判定是否是内部命令 */

	execute_disk_command();
		
	return 0;
}

/****************************************************************************
 * @fn		get_command
 *
 * @brief	解析简单命令到cmd[i]中，提取命令参数到avline数组中，并且将
 *			command结构体中的args[]中的每个指针指向avline的字符串
 *
 * @param	None
 *			
 * @return	succeed：the numbers of command	 error: -1
****************************************************************************/
void get_command(int i)
{
	int j = 0;
	int inword = 0;
	
	/* cat < test.txt |grep -n public > test2.txt & */
	while(*lineptr != '\0')
	{
		/* 去除空格 */
		while(*lineptr == ' ' || *lineptr == '\t')
			lineptr++;
		/* 将第i个参数指向avptr */
		cmd[i].args[j] = avptr;

		/* 参数提取 */
		while(*lineptr != '\0'
			&& *lineptr != ' '
			&& *lineptr != '\t'
			&& *lineptr != '\n'
			&& *lineptr != '>'
			&& *lineptr != '<'
			&& *lineptr != '|'
			&& *lineptr != '&')
		{
			/* 参数提取 */
			*avptr++ = *lineptr++;
			inword = 1;
		}
		*avptr++ = '\0';
		switch (*lineptr)
		{
			/* 解析下一个名参数 */
			case ' ':
			case '\t':
				inword = 0;
				j++;
				break;
			/* 当前命令参数解析完毕 */
			case '<':
			case '>':
			case '|':
			case '&':
			case '\n':
				if(inword == 0)
				{
					cmd[i].args[j] = NULL;
				}
				return ;
				
			default:	/* for '\0' */
				return ;
		}
		
			
	}
}


/****************************************************************************
 * @fn		get_command
 *
 * @brief	将lineptr 中的字符串与str进行匹配
 *
 * @param	str：要匹配的字符串
 *			
 * @return	succeed：1lineptr 移过所匹配的字符串	 error: 0 lineptr 保持不变
****************************************************************************/
int check(const char *str)
{
	char *p;
	
	while(*lineptr == ' ' || *lineptr == '\t')
		lineptr++;

	p = lineptr;
	while(*str != '\0' && *str == *p)
	{
		str++;
		p++;
	}

	if(*str == '\0')
	{
		lineptr = p;	/* lineptr 移过所匹配的字符串 */
		return 1;
	}
	
	return 0;
}

void getname(char *name)
{
	while (*lineptr == ' ' || *lineptr == '\t')
		lineptr++;

	while (*lineptr != '\0'
			&& *lineptr != ' '
			&& *lineptr != '\t'
			&& *lineptr != '>'
			&& *lineptr != '<'
			&& *lineptr != '|'
			&& *lineptr != '&'
			&& *lineptr != '\n')
	{
			*name++ = *lineptr++;
	}
	*name = '\0';
}

void print_command(void)
{
	int i;
	int j;
	printf("cmd_count = %d\n", cmd_count);
	if(infile[0] != '\0')
		printf("infile = [%s]\n", infile);
	if(outfile[0] != '\0')
		printf("outfile = [%s]\n", outfile);
	for(i = 0; i < cmd_count; ++i)
	{
		j = 0;
		while(cmd[i].args[j] != NULL)
		{
			printf("[%s] ", cmd[i].args[j]);
			j++;
		}
		printf("\n");
	}
		
}



  

