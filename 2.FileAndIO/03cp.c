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

/* 命令格式: ./03cp src dest */
int main(int argc, char *argv[])
{
	int infd;
	int outfd;
	char buf[1024];
	int nread;
	
	if(argc != 3)
	{
		/* 指定到标准错误 */
		fprintf(stderr, "Usage %s src dest \n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	infd = open(argv[1], O_RDONLY);
	if(infd == -1)
		ERR_EXIT("open src error");
	
	if((outfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
		ERR_EXIT("open dest error");
	
	while((nread = read(infd, buf, 1024)) > 0)
	{
		write(outfd, buf, nread);
	}
	
	close(infd);
	close(outfd);
	
	return 0;
}