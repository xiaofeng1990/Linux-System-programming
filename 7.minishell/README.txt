minishell实现的功能
	简单命令解析
	管道行解析
	输入输出重定向解析
	一些内置命令实现
	简单的信号处理
	
gbd命令
gdb minishell
r 全速运行
bt 调用堆栈
p i 查看一个变量
b parse_command 在函数出设置断点
n 向下运行

父进程要等待子进程退出
要在父进程中调用 wait()

前台作业等待管道中子进程推出
前台作业将ctrl+c和ctrl+\恢复为默认动作，可推出当前执行子进程

后台作业需要注册 signal(SIGCHLD, SIG_IGN); 信号， 防止子进程的僵尸进程

正常情况下进程组ID（PGID）应该和当前子进程ID（PID相同）
[wxf@localhost 7.minishell]$ ps -xj
  PPID    PID   PGID    SID TTY       TPGID STAT   UID   TIME COMMAND
  3951   4743   4743   3951 pts/0      4743 R+    1000   0:00 ps -xj


但是我们子进程的PGID和父进程相同，导致父进程也能收到子进程ctrl+c信号，
我们应该将PGID = PID
这涉及到会话期的概念 setpgid()
[minishell]$ ps -xj
  PPID    PID   PGID    SID TTY       TPGID STAT   UID   TIME COMMAND
  3951   4761   4761   3951 pts/0      4761 S+    1000   0:00 ./minishell
  4761   4762   4761   3951 pts/0      4761 R+    1000   0:00 ps -xj
