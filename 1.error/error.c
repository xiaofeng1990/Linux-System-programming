#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int ret;
	ret = close(10);
	if(ret == -1)
		perror("close error");
	if(ret == -1)
		/* 将错误编码转换为文本 */
		fprintf(stderr, "close error with msq: %s\n", strerror(errno));
	
	printf("EINTR DESC = %s\n", strerror(EINTR));
	return 0;
}


