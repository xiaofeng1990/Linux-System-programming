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

void set_flag(int fd, int flags);
void clear_flag(int fd, int flags);

int main(int argc, char *argv[])
{
	
	char buf[1024] = {0};
	int ret = 0;
	
	set_flag(0, O_NONBLOCK);
	clear_flag(0, O_NONBLOCK);
	/* 从标准输入中读数据 默认阻塞*/
	ret = read(0, buf, 1024);
	if(ret == -1)
		ERR_EXIT("read error\n");
	printf("buf = %s\n", buf);
	
	return 0;
}


void set_flag(int fd, int flags)
{
	int val;
	int ret = 0;
	/* 获得文件标志 */
	val = fcntl(fd, F_GETFL, 0);
	if(val == -1)
		ERR_EXIT("fcntl get flag error");
	
	
	/* 设置状态 */
	ret = fcntl(0, F_SETFL, val | flags);
	if(ret == -1)
		ERR_EXIT("fcntl set flag error");
}

void clear_flag(int fd, int flags)
{
	int val;
	int ret = 0;
	/* 获得文件标志 */
	val = fcntl(fd, F_GETFL, 0);
	if(val == -1)
		ERR_EXIT("fcntl get flag error");
	
	/* 设置状态 */
	ret = fcntl(0, F_SETFL, val & ~flags);
	if(ret == -1)
		ERR_EXIT("fcntl set flag error");
}		
	