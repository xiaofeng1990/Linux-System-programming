1.什么是进程
	从用户的角度来看进程是程序的一次执行过程
	从操作系统的核心来看，进程是操作系统分配的内存、CPU时间片等资源的基本单位。
	进程是资源分配的最小单位
	每一个进程都有自己独立的地址空间与执行状态。
	像UNIX这样的多任务操作系统能够让许多程序同时运行，每一个运行着的程序就构成了一个进程
2.进程包括
	代码段 + 数据段 + 堆栈段 + PCB

3.进程状态变迁
	运行状态（TASK_RUNNING）
	可中断睡眠状态（TASK_INTERRUPTIBLE）
	不可中断睡眠状态（TASK_UNINTERRUPTIBLE）
	暂停状态（TASK_STOPPED）
	僵死状态（TASK_ZOMBIE）

4.进程控制块
	进程描述信息
		进程标识符用于唯一的标识一个进程。
	进程控制信息
		进程当前状态
		进程优先级
		程序开始地址
		各种计时信息
		通信信息
	资源信息
		占用内存大小及管理用数据结构指针
		交换区相关信息
		I/O设备号、缓冲、设备相关的数结构
		文件系统相关指针
	现场保护信息
		寄存器
		PC
		程序状态字PSW
		栈指针


5.进程创建
	不同的操作系统所提供的进程创建原语的名称和格式不尽相同，但执行创建进程原语后，操作系统所做的工作却大致相同，都包括以下几点：
	给新创建的进程分配一个内部标识，在内核中建立进程结构。
	复制父进程的环境
	为进程分配资源， 包括进程映像所需要的所有元素（程序、数据、用户栈等），
	复制父进程地址空间的内容到该进程地址空间中。
	置该进程的状态为就绪，插入就绪队列。

6.进程撤消
	进程终止时操作系统做以下工作：
	关闭软中断:
		因为进程即将终止而不再处理任何软中断信号；
	回收资源：
		释放进程分配的所有资源，如关闭所有已打开文件，释放进程相应的数据结构等；
	写记帐信息：
		将进程在运行过程中所产生的记帐数据（其中包括进程运行时的各种统计信息）记录到一个全局记帐文件中；
	置该进程为僵死状态:
		向父进程发送子进程死的软中断信号，将终止信息status送到指定的存储单元中；
	转进程调度:
		因为此时CPU已经被释放，需要由进程调度进行CPU再分配。

7.终止进程的五种方法
	正常退出
		从main函数返回
		调用exit
		1.c库函数， 2.调用终止处理程序，清除IO缓冲区，操作内核
		调用_exit
		1.系统调用函数，2.直接操作内核
	异常退出
		调用abort
		由信号终止

	
	调用终止处理程
	atexit可以注册终止处理程序，ANSI C规定最多可以注册32个终止处理程序。
	终止处理程序的调用与注册次序相反
	int atexit(void (*function)(void));  //指针函数

	
8.fork
	使用fork函数得到的子进程从父进程的继承了整个进程的地址空间，包括：进程上下文、进程堆栈、内存信息、
	打开的文件描述符(文件共享)、信号控制设置、进程优先级、进程组号、当前工作目录、根目录、资源限制、控制终端等。
	fork的两次返回是在各自的进程地址空间返回的，在fork之后会产生两个进程，
	子进程与父进程的区别在于：
		1、父进程设置的锁，子进程不继承
		2、各自的进程ID和父进程ID不同
		3、子进程的未决告警被清除；
		4、子进程的未决信号集设置为空集。

	包含头文件 <sys/types.h> 和 <unistd.h>
	函数功能:创建一个子进程
	函数原型
			 pid_t  fork(void);
	参数：无参数。
	返回值:
		如果成功创建一个子进程，对于父进程来说返回子进程ID
		如果成功创建一个子进程，对于子进程来说返回值为0
		返回两次的原因：因为PCB里包含PID 和PPID ，对于子进程可以获得PPID 但是父进程不可能获得子进程信息
		如果为-1表示创建失败
	
	孤儿进程
	如果父进程先退出，子进程还没退出那么子进程的父进程将变为init进程，子进程变成孤儿进程，其实是托孤给1号进程。
	（注：任何一个进程都必须有父进程）
	僵尸进程
	如果子进程先退出，父进程还没退出，那么子进程必须等到父进程捕获到了子进程的退出状态才真正结束，否则这个时候子进程就成为僵进程。
    
	系统怎么实现fork（写时复制概念）
	如果多个进程要读取它们自己的那部分资源的副本，那么复制是不必要的。（代码段是共享的，代码段不可更改）
	每个进程只要保存一个指向这个资源的指针就可以了。
	如果一个进程要修改自己的那份资源的“副本”，那么就会复制那份资源。这就是写时复制的含义， 变量会复制一份，子进程的修改不会影响父进程
	
	fork 和 vfork 选择
	
	在fork还没实现copy on write之前。Unix设计者很关心fork之后立刻执行exec所造成的地址空间浪费，所以引入了vfork系统调用。
	vfork有个限制，子进程必须立刻执行_exit或者exec函数。
	即使fork实现了copy on write，效率也没有vfork高，但是我们不推荐使用vfork，因为几乎每一个vfork的实现，都或多或少存在一定的问题
	
8.替换进程镜像	
	execve 
		int execve(const char *filename, char *const argv[], char *const envp[]);

	exec替换进程映象

		包含头文件<unistd.h>
		功能用exec函数可以把当前进程替换为一个新进程。exec名下是由多个关联函数组成的一个完整系列，头文件<unistd.h>
		原型
		 int execl(const char *path, const char *arg, ...);
		 int execlp(const char *file, const char *arg, ...);
		 int execle(const char *path, const char *arg,
					  ..., char * const envp[]);
		 int execv(const char *path, char *const argv[]);
		 int execvp(const char *file, char *const argv[]);
	参数
	path参数表示你要启动程序的名称包括路径名
	arg参数表示启动程序所带的参数
	返回值:成功返回0,失败返回-1


	在进程的创建上Unix采用了一个独特的方法，它将进程创建与加载一个新进程映象分离。这样的好处是有更多的余地对两种操作进行管理。
	当我们创建了一个进程之后，通常将子进程替换成新的进程映象，这可以用exec系列的函数来进行。当然，exec系列的函数也可以将当前进程替换掉。
	fork创建一个进程，新进程和原进程是一样的，如果要创建的新进程执行其他的程序，需要用exec替换进程镜像
	进程替换不改变进程号
	
9.SIGCHLD 信号
	当子进程退出的时候，内核会向父进程发送SIGCHLD信号，子进程的退出是个异步事件（子进程可以在父进程运行的任何时刻终止）
	子进程退出时，内核将子进程置为僵尸状态，这个进程称为僵尸进程，它只保留最小的一些内核数据结构，以便父进程查询子进程的退出状态。
	父进程查询子进程的退出状态可以用wait/waitpid函数
	父进程可注册该信号 signal()
	
	pid_t waitpid(pid_t pid, int *status,int options)
		参数:
		status:如果不是空，会把状态信息写到它指向的位置
		options：允许改变 waitpid 的行为，最有用的一个选项是 WNOHANG ,它的作用是防止 waitpid 把调用者的执行挂起
		返回值：如果成功返回等待子进程的ID，失败返回-1


		The value of pid can be:

		   < -1   meaning wait for any child process whose process group ID is equal to the absolute value of pid.
			waitpid(-100)  进程组 = 100，组内的任一子进程
		   -1     meaning wait for any child process.

		   0      meaning wait for any child process whose process group ID is equal to that of the calling process.

		   > 0    meaning wait for the child whose process ID is equal to the value of pid.
	   
	如何避免僵进程
		调用wait或者waitpid函数查询子进程退出状态，此方法父进程会被挂起。
		
		如果不想让父进程挂起，可以在父进程中加入一条语句： signal(SIGCHLD,SIG_IGN);
		表示父进程忽略SIGCHLD信号，该信号是子进程退出的时候向父进程发送的。
system
	功能：system()函数调用“/bin/sh -c command”执行特定的命令，阻塞当前进程直到command命令执行完毕
	原型：
		int system(const char *command);
	返回值：
		如果无法启动shell运行命令，system将返回127；出现不能执行system调用的其他错误时返回-1。如果system能够顺利执行，返回那个命令的退出码。
	system函数执行时，会调用fork、execve、waitpid等函数。

什么是守护进程
	守护进程是在后台运行不受控端控制的进程，通常情况下守护进程在系统启动时自动运行
	守护进程的名称通常以d结尾，比如sshd、xinetd、crond等

	linux系统启动步骤
	会话期