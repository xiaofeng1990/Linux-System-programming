
typedef void (*__sighandler_t) (int);
#define SIG_ERR ((__sighandler_t) -1)	//信号注册失败
#define SIG_DFL ((__sighandler_t) 0)	//注册函数 忽略信号动作
#define SIG_IGN ((__sighandler_t) 1)	//注册函数 信号默认动作

1.注册信号函数原型:
	__sighandler_t signal(int signum, __sighandler_t handler);
	参数
	signal是一个带signum和handler两个参数的函数，准备捕捉或屏蔽的信号由参数signum给出，接收到指定信号时将要调用的函数由handler给出
	handler这个函数必须有一个int类型的参数（即接收到的信号代码），它本身的类型是void
	handler也可以是下面两个特殊值：
			SIG_IGN	屏蔽该信号
			SIG_DFL	恢复默认行为

	返回值: __sighandler_t
		先前signal注册相同信号的handler
		signal(SIGINT, handler);
		signal(SIGINT, handler2);	//返回值为handler
	SIGINT(ctrl+c)   2
	SIGQUIT(ctrl+\)  3
	
	1) SIGHUP	 2) SIGINT	 3) SIGQUIT	 4) SIGILL	 5) SIGTRAP
	6) SIGABRT	 7) SIGBUS	 8) SIGFPE	 9) SIGKILL	10) SIGUSR1
	11) SIGSEGV	12) SIGUSR2	13) SIGPIPE	14) SIGALRM	15) SIGTERM
	16) SIGSTKFLT	17) SIGCHLD	18) SIGCONT	19) SIGSTOP	20) SIGTSTP
	21) SIGTTIN	22) SIGTTOU	23) SIGURG	24) SIGXCPU	25) SIGXFSZ
	26) SIGVTALRM	27) SIGPROF	28) SIGWINCH	29) SIGIO	30) SIGPWR
	31) SIGSYS	34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
	38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
	43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
	48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
	53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
	58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
	63) SIGRTMAX-1	64) SIGRTMAX	

2.可靠信号
	支持队列，不会丢失, 实时信号
	SIGRTMIN 34
	到SIGRTMAX 64
	信号的发送和安装也出现了新版本：信号发送函数sigqueue()及信号安装函数sigaction()（不需重新安装）。
	
3.信号发送
	kill 向pid发送9号信号，杀死进程，不可被忽略，不可被捕获
	 #include <signal.h>

	int kill(pid_t pid, int sig);
		pid>0:  信号sig发送给pid = pid的进程
		pid=0： 信号sig将被发送给调用者所在组中的每一个进程
		pid=-1：信号sig将被发送给调用者进程有权限发送的每一个进程，除了1号进程和自身之外
		pid<-1: 信号将发送给进程组 = -pid 中的每一个进程
			
	raise
		给自己发送信号。raise(sig)等价于kill(getpid(), sig);
	killpg
		给进程组发送信号。killpg(pgrp, sig)等价于kill(-pgrp, sig);
	sigqueue 可靠信号
		给进程发送信号，支持排队，可以附带信息。
	
	函数 		可发送的信号
	alarm        SIGALRM
	setitimer    SIGALRM SIGVTALRM SIGPROF
	abort        SIGABRT

4.pause
	将进程置为可中断睡眠状态。然后它调用schedule()，使linux进程调度器找到另一个进程来运行。
	pause使调用者进程挂起，直到一个信号被捕获
	
5.不可重入
	为了增强程序的稳定性，在信号处理函数中应使用可重入函数。 
	所谓可重入函数是指一个可以被多个任务调用的过程，任务在调用时不必担心数据是否会出错。因为进程在收到信号后，就将跳转到信号处理函数去接着执行。如果信号处理函数中使用了不可重入函数，那么信号处理函数可能会修改原来进程中不应该被修改的数据，这样进程从信号处理函数中返回接着执行时，可能会出现不可预料的后果。不可再入函数在信号处理函数中被视为不安全函数。
	满足下列条件的函数多数是不可再入的：（1）使用静态的数据结构，如getlogin()，gmtime()，getgrgid()，getgrnam()，getpwuid()以及getpwnam()等等；（2）函数实现时，调用了malloc（）或者free()函数；（3）实现时使用了标准I/O函数的

6.信号在内核中的表示
	执行信号的处理动作称为信号递达（Delivery），信号从产生到递达之间的状态，称为信号未决（Pending）。
	进程可以选择阻塞（Block）某个信号。被阻塞的信号产生时将保持在未决状态，直到进程解除对此信号的阻塞，
	才执行递达的动作。注意，阻塞和忽略是不同的，只要信号被阻塞就不会递达，而忽略是在递达之后可选的一种处
	理动作。信号在内核中的表示可以看作是这样的
	
	//使用方法参考07sigstaus.c
	
	信号集操作函数 64位
	#include <signal.h>
	
	
	//将64位都清零
	int sigemptyset(sigset_t *set);
	//将64位都置为1
	int sigfillset(sigset_t *set);
	//将信号对应的位置1
	int sigaddset(sigset_t *set, int signo);
	//将信号对应的位置0
	int sigdelset(sigset_t *set, int signo);
	//检测信号对应的状态
	int sigismember(const sigset_t *set, int signo);

	#include <signal.h>
	int sigprocmask(int how, const sigset_t *set, sigset_t *oset);
	功能：读取或更改进程的信号屏蔽字。
	返回值：若成功则为0，若出错则为-1
	如果oset是非空指针，则读取进程的当前信号屏蔽字通过oset参数传出。如果set是非空指针，则更改进程的信号屏蔽字，
	参数how指示如何更改。如果oset和set都是非空指针，则先将原来的信号屏蔽字备份到oset里，然后根据set和how参数更
	改信号屏蔽字。假设当前的信号屏蔽字为mask，下表说明了how参数的可选值。

	
7.sigaction
	包含头文件<signal.h>
	功能:sigaction函数用于改变进程接收到特定信号后的行为。
	原型：
	int  sigaction(int signum,const struct sigaction *act,const struct sigaction *old);
	参数
	该函数的第一个参数为信号的值，可以为除SIGKILL及SIGSTOP外的任何一 个特定有效的信号（为这两个信号定义自己的处理函数，将导致信号安装错误）
	第二个参数是指向结构sigaction的一个实例的指针，在结构 sigaction的实例中，指定了对特定信号的处理，可以为空，进程会以缺省方式对信号处理
	第三个参数oldact指向的对象用来保存原来对相应信号的处理，可指定oldact为NULL。
	返回值:函数成功返回0，失败返回-1

	struct sigaction {
			void (*sa_handler)(int);		//不可靠信号安装
			void (*sa_sigaction)(int, siginfo_t *, void *);	//可靠信号安装，
			sigset_t sa_mask;		//信号排队
			int sa_flags;
			void (*sa_restorer)(void);
		};
		
8.sigqueue函数
	功能:新的发送信号系统调用,主要是针对实时信号提出的支持信号带有参数,与函数sigaction()配合使用。
	原型:
		int sigqueue(pid_t pid, int sig, const union sigval value);
	参数
	 sigqueue的第一个参数是指定接收信号的进程id，
	 第二个参数确定即将发送的信号，
	 第三个参数是一个联合数据结构union sigval，指定了信号传递的参数，即通常所说的4字节值。
	 返回值成功返回0,失败返回-1 
	typedef union sigval
	 { 
		int sival_int; 
		void *sival_ptr; 
	}sigval_t; 

	The siginfo_t argument to sa_sigaction is a struct with the following elements:

	   siginfo_t {
		   int      si_signo;    /* Signal number */
		   int      si_errno;    /* An errno value */
		   int      si_code;     /* Signal code */
		   int      si_trapno;   /* Trap number that caused
									hardware-generated signal
									(unused on most architectures) */
		   pid_t    si_pid;      /* Sending process ID */
		   uid_t    si_uid;      /* Real user ID of sending process */
		   int      si_status;   /* Exit value or signal */
		   clock_t  si_utime;    /* User time consumed */
		   clock_t  si_stime;    /* System time consumed */
		   sigval_t si_value;    /* Signal value */
		   int      si_int;      /* POSIX.1b signal */
		   void    *si_ptr;      /* POSIX.1b signal */
		   int      si_overrun;  /* Timer overrun count; POSIX.1b timers */
		   int      si_timerid;  /* Timer ID; POSIX.1b timers */
		   void    *si_addr;     /* Memory location which caused fault */
		   long     si_band;     /* Band event (was int in
									glibc 2.3.2 and earlier) */
		   int      si_fd;       /* File descriptor */
		   short    si_addr_lsb; /* Least significant bit of address
									(since Linux 2.6.32) */
	   }
	int sa_flags 参数; 
	   SA_NOCLDSTOP
			  If  signum  is SIGCHLD, do not receive notification when child processes stop (i.e., when they 
			  receive one of SIGSTOP, SIGTSTP, SIGTTIN or SIGTTOU) or resume (i.e., they receive SIGCONT)
			  (see wait(2)).  This flag is meaningful only when establishing a handler for SIGCHLD.

	   SA_NOCLDWAIT (since Linux 2.6)
			  If signum is SIGCHLD, do not transform children into zombies when they terminate.  
			  See also waitpid(2).  This flag is meaningful only when establishing a handler  for  SIGCHLD,  or  when
			  setting that signal's disposition to SIG_DFL.

			  If the SA_NOCLDWAIT flag is set when establishing a handler for SIGCHLD, POSIX.1 leaves it 
			  unspecified whether a SIGCHLD signal is generated when a child process terminates.  On Linux, a
			  SIGCHLD signal is generated in this case; on some other implementations, it is not.

	   SA_NODEFER
			  Do not prevent the signal from being received from within its own signal handler.  
			  This flag is meaningful only when establishing a signal handler.  SA_NOMASK is an obsolete, nonstandard
			  synonym for this flag.

	   SA_ONSTACK
			  Call  the  signal  handler on an alternate signal stack provided by sigaltstack(2).  
			  If an alternate stack is not available, the default stack will be used.  This flag is meaningful only
			  when establishing a signal handler.

	   SA_RESETHAND
			  Restore the signal action to the default upon entry to the signal handler.  This flag is meaningful only 
			  when establishing a signal handler.  SA_ONESHOT is an obsolete, nonstandard  syn‐
			  onym for this flag.

	   SA_RESTART
			  Provide  behavior  compatible  with BSD signal semantics by making certain system calls restartable 
			  across signals.  This flag is meaningful only when establishing a signal handler.  See
			  signal(7) for a discussion of system call restarting.

	   SA_SIGINFO (since Linux 2.2)
			  The signal handler takes three arguments, not one.  In this case, sa_sigaction should be set instead 
			  of sa_handler.  This flag is meaningful only when establishing a signal handler.
				  
	sa_flags = SA_SIGINFO 才能接收数据

