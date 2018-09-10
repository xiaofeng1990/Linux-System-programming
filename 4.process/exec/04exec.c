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
	printf("Entering main ...\n");
	int ret = execl("/bin/ls", "ls", "-l", NULL);
	if (ret == -1)
		perror("execl error");
	//execlp("ls", "ls", "-l", NULL);
	printf("Exiting main ...\n");
	return 0;
}
