#include "parse.h"
#include <stdio.h>
#include "init.h"
#include "def.h"
#include <sys/time.h>
#include <sys/resource.h>

char cmdline[MAXLINE + 1];		/* 输入命令行缓存 */
char avline[MAXLINE + 1];		/* 命令解析缓存 */
char *lineptr;					/* 指向 lineptr */
char *avptr;					/* 指向 avline */

char infile[MAXNAME + 1];		/* 输入文件名 */
char outfile[MAXNAME + 1];		/* 输出文件名 */

int cmd_count = 0;				/* 命令个数 */
int backgnd = 0;				/* 是否后台运行 */
int append = 0;
int lastpid;
int open_max;
struct command cmd[PIPELINE];	/* 命令参数结构体 */

int main()
{

	struct rlimit limit;
	if(getrlimit(RLIMIT_NOFILE,&limit) == -1)
			ERR_EXIT("getrlimit error\n");
	printf("getrlimit = %d\n",(int)limit.rlim_cur);
	open_max = (int)limit.rlim_cur;

	
	setup();
	shell_loop();
	printf("minishell\n");
	return 0;
}


