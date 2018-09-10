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

int main(int argc, char *argv[])
{
	//char *const args[] = {"ls", "-l", NULL};
	printf("Entering main ...\n");
	
	/* 可变参数 */
	execlp("ls", "ls", "-l", NULL);
	
	/* 不可变参数 */
	//execvp("ls", args);
	printf("Exiting main ...\n");
	return 0;
}
