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
	char * const envp[] = {"AA=11", "BB=22", NULL};
	printf("Entering main ...\n");
	//execl("./hello", "hello", NULL);
	execle("./hello", "hello", NULL, envp);
	printf("Exiting main ...\n");
	return 0;
}
