#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

int main(int argc, char *argv[])
{
	int fd;
	fd = open("test2.txt", O_WRONLY);
	if (fd == -1)
		ERR_EXIT("open error");

	close(1);
	
	/* 复制文件描述符，进行重定向 */
	if(fcntl(fd, F_DUPFD, 0) < 0)
		ERR_EXIT("dup fd drror\n");
	
	printf("hello\n");
	printf("hhh\n");
	printf("hhh\n");
	printf("hhh\n");
	return 0;
}
