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
 * @fn      builtin
 *
 * @brief   内部命令解析
 *
 * @param   None
 *			
 * @return  1 执行内部命令， 0外部命令
****************************************************************************/
int builtin(void)
{
	if(check("exit"))
		do_exit();
	else if(check("cd"))
		do_cd();
	else 
		return 0;

	return 1;
	
}
void do_exit(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
	
}

void do_cd(void)
{
	printf("do cd\n");
}