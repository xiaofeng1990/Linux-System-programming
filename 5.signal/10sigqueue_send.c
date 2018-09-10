#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
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
	pid_t pid;
	union sigval value;
	
	if (argc != 2)
	{
		fprintf(stderr, "Usage %s pid\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	pid = atoi(argv[1]);
	printf("pid = %d\n", pid);
	value.sival_int = 100;
	sigqueue(pid, SIGINT, value);
	return 0;
}
