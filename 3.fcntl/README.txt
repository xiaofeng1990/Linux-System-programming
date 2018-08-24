

功能：操纵文件描述符，改变已打开的文件的属性

int fcntl(int fd, int cmd, ... /* arg */ );


复制文件描述符
	F_DUPFD (long)
文件描述符标志
	F_GETFD (void)
	F_SETFD (long)
文件状态标志
	F_GETFL (void)
	F_SETFL (long)
文件锁
	F_GETLK
	F_SETLK，非阻塞加锁
	F_SETLKW 阻塞加锁

1.改变文件描述符 F_DUPFD (long)
	fcntl(fd, F_DUPFD, 0)
	第三个参数表示搜索文件描述符的起始位置，直到找到未使用的文件描述符

2.文件状态标志
	 获得文件状态标志
	flags = fcntl(0, F_GETFL, 0); 
	fcntl(0, F_SETFL, val & ~flags);

3.文件锁
