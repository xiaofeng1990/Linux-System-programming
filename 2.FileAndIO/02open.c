#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)


int main(void)
{
	umask(0);
	int fd;
	fd = open("test2.txt", O_WRONLY | O_CREAT | O_EXCL, S_IRWXU | S_IWUSR);
	if(fd == -1)
	{
		ERR_EXIT("open error");
	}
	printf("open succ\n");
	close(fd);
	return 0;
}