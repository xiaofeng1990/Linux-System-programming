#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>


#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)


/* 进程替换 */		
int main(int argc, char *argv[])
{
	printf("Entering main ....\n");
	
	execlp("ls", "ls", "-l", NULL);
	
	/* 程序跳进ps程序中，不会向下继续进行 */
	printf("Exiting main ....\n");
	
	return 0;
}