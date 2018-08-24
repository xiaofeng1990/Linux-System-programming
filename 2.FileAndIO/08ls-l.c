#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

#define ERR_EXIT(m) \
	do \
	{ \
		perror(m); \
		exit(EXIT_FAILURE); \
	} while(0)

void fileperm(struct stat *buf, char *perm);

int main(void)
{
	/* 打开当前目录 */
	static struct stat sbuf;
	struct group *group_info;
	struct passwd *own_info;
	struct tm *time_info;
	char perm[11] = {0};
	DIR *dir = opendir(".");
	struct dirent *de;
	char time_buf[20];
	
	while((de = readdir(dir)) != NULL)
	{

		if(strncmp(de->d_name, ".", 1) == 0)
			continue;
		memset(&sbuf, 0, sizeof(struct stat));
		memset(time_buf, 0, sizeof(time_buf));
		
		if(lstat(de->d_name, &sbuf) == -1)
			ERR_EXIT("get stat error");
		fileperm(&sbuf, perm);
		/* 打印权限 */
		printf("%s ", perm);
		
		/* 打印连接数 */
		printf("%d ", (int)sbuf.st_nlink);
		
		/* 打印拥有组 */
		group_info = getgrgid(sbuf.st_gid);
		
		printf("%s ", group_info->gr_name);
		
		/* 打印拥有者 */
		own_info = getpwuid(sbuf.st_uid);
		printf("%s ", own_info->pw_name);
		
		/* 打印文件大小 */
		printf("%5d ", (int)sbuf.st_size);
		
		/* 打印文件最后修改日期 */
		time_info = localtime(&sbuf.st_mtime);
		   
		strftime(time_buf, sizeof(time_buf), "%b %d %R", time_info);
		printf("%s  ", time_buf);
		/* 打印文件名 */
		printf("%s\n", de->d_name);
	}
	
	
	closedir(dir);
	exit(EXIT_FAILURE);
}


void fileperm(struct stat *buf, char *perm)
{
	strcpy(perm, "----------");
	perm[0] = '?';
	mode_t mode;
	mode = buf->st_mode;
	switch (mode & S_IFMT)
	{
		case S_IFSOCK:
		perm[0] = 's';
			break;
		case S_IFLNK:
		perm[0] = 'l';
			break;
		case S_IFREG:
		perm[0] = '-';
			break;
		case S_IFBLK:
		perm[0] = 'b';
			break;
		case S_IFDIR:
		perm[0] = 'd';
			break;
		case S_IFCHR:
		perm[0] = 'c';
			break;
		case S_IFIFO:
		perm[0] = 'p';
			break;
	}

	if (mode & S_IRUSR)
		perm[1] = 'r';
	if (mode & S_IWUSR)
		perm[2] = 'w';
	if (mode & S_IXUSR)
		perm[3] = 'x';
	if (mode & S_IRGRP)
		perm[4] = 'r';
	if (mode & S_IWGRP)
		perm[5] = 'w';
	if (mode & S_IXGRP)
		perm[6] = 'x';
	if (mode & S_IROTH)
		perm[7] = 'r';
	if (mode & S_IWOTH)
		perm[8] = 'w';
	if (mode & S_IXOTH)
		perm[9] = 'x';
	perm[10] = '\0';
}
