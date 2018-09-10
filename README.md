# Linux-System-programming
linux系统知识点讲解实例编程
1.标准错误输出
	将错误缓存区的错误类型输出到标准输出
	perror("close error");
	
	指定输出方向到标准输出 strerror(errno)获得错误类型字符串
	fprintf(stderr, "close error with msq: %s\n", strerror(errno));
2.文件IO
3.fcntl函数用法
4.关于进程的函数和知识点
5.信号
6.管道
7.一个minishell

