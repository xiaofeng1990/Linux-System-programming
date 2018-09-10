#ifndef _DEF_H_
#define _DEF_H_
#include <stdio.h>
#include <stdlib.h>

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)
	
/* 输入行最大长度 */
#define MAXLINE 1024

/* 每个简单命令参数最多个数 */
#define MAXARG 20

/* 一个管道行中简单命令的最多个数 */
#define PIPELINE 5

/* IO重定向文件名的最大长度 */
#define MAXNAME 100

struct command{
	char *args[MAXARG + 1];	/* 解析出的简单参数列表 */	
};

#endif	/* _DEF_H_ */
