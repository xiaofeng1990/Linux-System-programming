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
	/* 避免僵尸进程 */
	signal(SIGCHLD, SIG_IGN);
	printf("before fork pid = %d\n", getpid());
	int fd;
	fd = open("test.txt", O_WRONLY);
	if (fd == -1)
		ERR_EXIT("open error");

	
	pid_t pid;
	pid = fork();
	if (pid == -1)
		ERR_EXIT("fork error");

	if (pid > 0)
	{
		printf("this is parent pid=%d childpid=%d\n", getpid(), pid);
		write(fd, "parent", 6);
		sleep(5);
	}
	else if (pid == 0)
	{
		printf("this is child pid=%d parentpid=%d\n", getpid(), getppid());
		write(fd, "child", 5);
	}
	return 0;
}