什么是管道
	我们把从一个进程连接到另一个进程的一个数据流称为一个“管道”
本质：具有特定大小的内核缓冲区

特点
	管道是半双工的，数据只能向一个方向流动；需要双方通信时，需要建立起两个管道
	只能用于具有共同祖先的进程（具有亲缘关系的进程）之间进行通信；通常，一个管道由一个进程创建，然后该进程调用fork，此后父、子进程之间就可应用该管道。
匿名管道pipe
	包含头文件<unistd.h>
	功能:创建一无名管道
	原型
	int pipe(int fd[2]);
	参数
	fd：文件描述符数组,其中fd[0]表示读端, fd[1]表示写端
	返回值:成功返回0，失败返回错误代码
	
管道读写规则
当没有数据可读时
	O_NONBLOCK disable：read调用阻塞，即进程暂停执行，一直等到有数据来到为止。
	O_NONBLOCK enable：read调用返回-1，errno值为EAGAIN。fcntl(pipefd[0], F_SETFL, flags | O_NONBLOCK);
当管道满的时候
	O_NONBLOCK disable： write调用阻塞，直到有进程读走数据
	O_NONBLOCK enable：调用返回-1，errno值为EAGAIN
如果所有管道写端对应的文件描述符被关闭，则read返回0
如果所有管道读端对应的文件描述符被关闭，则write操作会产生信号SIGPIPE
当要写入的数据量不大于PIPE_BUF时，linux将保证写入的原子性。单个进程写入数据的连续性
当要写入的数据量大于PIPE_BUF时，linux将不再保证写入的原子性

PIPE_BUF
       POSIX.1-2001  says  that write(2)s of less than PIPE_BUF bytes must be atomic: the output data is written to the pipe as a contiguous sequence.  Writes of more than PIPE_BUF bytes may be nonatomic:
       the kernel may interleave the data with data written by other processes.  POSIX.1-2001 requires PIPE_BUF to be at least 512 bytes.  (On Linux, PIPE_BUF is 4096 bytes.)  The precise semantics depend
       on whether the file descriptor is nonblocking (O_NONBLOCK), whether there are multiple writers to the pipe, and on n, the number of bytes to be written:

       O_NONBLOCK disabled, n <= PIPE_BUF
              All n bytes are written atomically; write(2) may block if there is not room for n bytes to be written immediately

       O_NONBLOCK enabled, n <= PIPE_BUF
              If there is room to write n bytes to the pipe, then write(2) succeeds immediately, writing all n bytes; otherwise write(2) fails, with errno set to EAGAIN.

       O_NONBLOCK disabled, n > PIPE_BUF
              The write is nonatomic: the data given to write(2) may be interleaved with write(2)s by other process; the write(2) blocks until n bytes have been written.

       O_NONBLOCK enabled, n > PIPE_BUF
              If  the pipe is full, then write(2) fails, with errno set to EAGAIN.  Otherwise, from 1 to n bytes may be written (i.e., a "partial write" may occur; the caller should check the return value
              from write(2) to see how many bytes were actually written), and these bytes may be interleaved with writes by other processes.
			  
命名管道（FIFO）
	管道应用的一个限制就是只能在具有共同祖先（具有亲缘关系）的进程间通信。
	如果我们想在不相关的进程之间交换数据，可以使用FIFO文件来做这项工作，它经常被称为命名管道。
	命名管道是一种特殊类型的文件
	
	命名管道可以从命令行上创建，命令行方法是使用下面这个命令：
			$ mkfifo filename
	命名管道也可以从程序里创建，相关函数有：
		int mkfifo(const char *filename,mode_t mode);
		
	如果当前打开操作是为读而打开FIFO时
	O_NONBLOCK disable：阻塞直到有相应进程为写而打开该FIFO
	O_NONBLOCK enable：立刻返回成功
	如果当前打开操作是为写而打开FIFO时
	O_NONBLOCK disable：阻塞直到有相应进程为读而打开该FIFO
	O_NONBLOCK enable：立刻返回失败，错误码为ENXIO
