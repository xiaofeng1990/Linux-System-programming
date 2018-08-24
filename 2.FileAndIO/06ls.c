#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>


#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

int main(void)
{
	/* 打开当前目录 */
	DIR *dir = opendir(".");
	struct dirent *de;
	while((de = readdir(dir)) != NULL)
	{
		if(strncmp(de->d_name, ".", 1) == 0)
			continue;
		
		printf("%s\n", de->d_name);
	}
	
	closedir(dir);
	exit(EXIT_FAILURE);
}