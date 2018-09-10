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

/* 进程替换，不改变进程号 */
int main(int argc, char *argv[])
{
	printf("Entering main ...\n");
	printf("pid=%d\n", getpid());
	execlp("./hello", "hello", NULL);
	//int ret = execlp("hello", "hello", NULL);
	//if (ret == -1)
	//	perror("execlp error");
	printf("Exiting main ...\n");
	return 0;
}
