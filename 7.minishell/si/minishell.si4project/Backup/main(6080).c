#include "parse.h"
#include <stdio.h>
#include "init.h"
#include "def.h"

char cmdline[MAXLINE + 1];
char avline[MAXLINE + 1];
struct command cmd;

int main()
{
	setup();
	shell_loop();
	printf("minishell\n");
	return 0;
}


