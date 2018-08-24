1.文件描述符
	当打开或者创建一个文件的时候，内核向进程返回一个文件描述符（非负整数）。后续对文件的操作只需通过该文件描述符，
	内核记录有关这个打开文件的信息
	
2.系统默认打开的文件
	标准输入	0（STDIN_FILENO）
	标准输出	1（STDOUT_FILENO）
	标准错误	2（STDERR_FILENO）

3.文件描述符与文件指针的转换
	fileno：将文件指针转换为文件描述符
	fdopen：将文件描述符转换为文件指针
4.open（）（打开）系统调用
	int open(const char *path, int flags);
	参数
	path ：文件的名称，可以包含（绝对和相对）路径
	flags：文件打开模式
	返回值
	打开成功，返回文件描述符；
	打开失败，返回－1

	int open(const char *path, int flags,mode_t mode);
	参数
	path ：文件的名称，可以包含（绝对和相对）路径
	flags：文件打开模式
	mode:  用来规定对该文件的所有者，文件的用户组及系	         统中其他用户的访问权限
	返回值
	打开成功，返回文件描述符；
	打开失败，返回－1
	
5.文件的打开方式
	O_ACCMODE       
	O_RDONLY        只读的方式打开
	O_WRONLY        只写的方式打开
	O_RDWR          读写的方式打开
	O_CREAT         打开文件，如果文件不存在就创建文件
	O_EXCL          如果已经设置O_CREAT，并且文件已经存在，就强制open()失败
	O_SYNC			以同步的方式打开，就是所有的write操作会阻塞在同步磁盘操作，直到同步完才返回
	O_NOCTTY        00000100
	O_TRUNC         在open()时，将文件的内容清空
	O_APPEND        写入的所有的数据将被追加到文件的末尾
	O_NONBLOCK      00000800
	O_DSYNC         00001000
	FASYNC          00002000
	O_NOFOLLOW      00020000
	
	所有这些标志值的符号名称可以通过#include <fcntl.h>访问


	ulimit -a
		core file size          (blocks, -c) 0
		data seg size           (kbytes, -d) unlimited
		scheduling priority             (-e) 0
		file size               (blocks, -f) unlimited
		pending signals                 (-i) 14473
		max locked memory       (kbytes, -l) 64
		max memory size         (kbytes, -m) unlimited
		open files                      (-n) 1024		//一个进程可支持打开最大文件数
		pipe size            (512 bytes, -p) 8
		POSIX message queues     (bytes, -q) 819200
		real-time priority              (-r) 0
		stack size              (kbytes, -s) 8192
		cpu time               (seconds, -t) unlimited
		max user processes              (-u) 4096
		virtual memory          (kbytes, -v) unlimited
		file locks                      (-x) unlimited
		
	查看系统支持打开最大文件数	
		cat /proc/sys/fs/file-max  
	队列属性信息路径
		/proc/sys/fs/mqueue

6.read 读操作
	ssize_t read(int fd, void *buf, size_t count);
	参数
	fd ：想要读的文件的文件描述符
	buf ： 指向内存块的指针，从文件中读取来的字节放到这个内存块中
	count ： 从该文件复制到buf中的字节个数，理论上读取的字节数
	返回值
	如果出现错误，返回-1
	读文件结束，返回0，表示读到文件尾
	大于0 否则返回从该文件复制到规定的缓冲区中的字节数，实际读到的字节数

7.write 写操作
	用write()系统调用将数据写到一个文件中 
	函数原型：
	ssize_t write(int fd, const void *buf, size_t count);
	函数参数：
	fd：要写入的文件的文件描述符
	buf： 指向内存块的指针，从这个内存块中读取数据写入	      到文件中
	count： 要写入文件的字节个数
	返回值
	如果出现错误，返回-1
	如果写入成功，则返回写入到文件中的字节个数
	返回值 >0 并不表示已经写到磁盘中去，仅仅表示写到内核的内存缓冲区
	
	如果要马上实现同步，可调用一下函数同步大磁盘
	int fsync(int fd);
	或者以O_SYNC方式打开

8.文件的随机读写
	off_t lseek(int fd, off_t offset, int whence);
	fd：需设置文件的文件描述符
	offset：偏移量
	whence：便宜的其实位置
		SEEK_SET
            The offset is set to offset bytes.
			从文件开始出偏移
       SEEK_CUR
            The offset is set to its current location plus offset bytes.
			从文件当前位置计算偏移
       SEEK_END
            The offset is set to the size of the file plus offset bytes.
			从文件尾计算偏移
			
	可以产生一个空洞文件，其实在磁盘中并没有存放空洞内容
	查看文件全部内容
	od -c hole.txt
	查看文件在磁盘中的大小
	du -h hole.txt
	
9.目录访问
	功能说明：打开一个目录
		#include <sys/types.h>
		#include <dirent.h>

		DIR *opendir(const char *name);
	返回值：
		打开成功：返回一个目录指针
		打开失败：返回0
	
	功能说明：访问制定目录中下一个链接的细节
		#include <dirent.h>

		struct dirent *readdir(DIR *dirp);
	返回值：
		返回一个指向 dirent 结构体的指针，它包含指定目录中下一个链接的细节；
		没有更多连接时，返回0
		
	功能说明：关闭一个已经打开的目录
		#include <sys/types.h>
		#include <dirent.h>

		int closedir(DIR *dirent)
	返回值：
		成功返回0
		失败返回-1
	
	rmdir	删除一个空目录
	mkdir 	创建一个目录
	chmod	更改一指定目录个文件的权限
	fchmod	根据文件描述符更改要给文件的权限
	chown	更改一指定目录个文件的拥有者
	fchown	根据文件描述符来更改文件的拥有者

	
	On Linux, the dirent structure is defined as follows:

           struct dirent {
               ino_t          d_ino;       /* inode number */
               off_t          d_off;       /* not an offset; see NOTES */
               unsigned short d_reclen;    /* length of this record */
               unsigned char  d_type;      /* type of file; not supported
                                              by all file system types */
               char           d_name[256]; /* filename */
           };

		
	 DIR 结构体的原型为：struct_dirstream

       在linux系统中：

        typedef struct __dirstream DIR;

       struct __dirstream
       {
         void *__fd; /* `struct hurd_fd' pointer for descriptor.   */
         char *__data; /* Directory block.   */
         int __entry_data; /* Entry number `__data' corresponds to.   */
         char *__ptr; /* Current pointer into the block.   */
         int __entry_ptr; /* Entry number `__ptr' corresponds to.   */
         size_t __allocation; /* Space allocated for the block.   */
         size_t __size; /* Total valid data in the block.   */
         __libc_lock_define (, __lock) /* Mutex lock for this structure.   */
        };
		
10. stat()获取文件属性

		#include <sys/types.h>
		#include <sys/stat.h>
		#include <unistd.h>

		int stat(const char *path, struct stat *buf);
		
		

	 struct stat {
				   dev_t     st_dev;     /* ID of device containing file */
				   ino_t     st_ino;     /* inode number */
				   mode_t    st_mode;    /* protection */
				   nlink_t   st_nlink;   /* number of hard links */
				   uid_t     st_uid;     /* user ID of owner */
				   gid_t     st_gid;     /* group ID of owner */
				   dev_t     st_rdev;    /* device ID (if special file) */
				   off_t     st_size;    /* total size, in bytes */
				   blksize_t st_blksize; /* blocksize for file system I/O */
				   blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
				   time_t    st_atime;   /* time of last access */
				   time_t    st_mtime;   /* time of last modification */
				   time_t    st_ctime;   /* time of last status change */
			   };

	S_ISREG(m)  is it a regular file?

           S_ISDIR(m)  directory?

           S_ISCHR(m)  character device?

           S_ISBLK(m)  block device?

           S_ISFIFO(m) FIFO (named pipe)?

           S_ISLNK(m)  symbolic link?  (Not in POSIX.1-1996.)

           S_ISSOCK(m) socket?  (Not in POSIX.1-1996.)

       The following flags are defined for the st_mode field:

           S_IFMT     0170000   bit mask for the file type bit fields
           S_IFSOCK   0140000   socket
           S_IFLNK    0120000   symbolic link
           S_IFREG    0100000   regular file
           S_IFBLK    0060000   block device
           S_IFDIR    0040000   directory
           S_IFCHR    0020000   character device
           S_IFIFO    0010000   FIFO
           S_ISUID    0004000   set-user-ID bit
           S_ISGID    0002000   set-group-ID bit (see below)
           S_ISVTX    0001000   sticky bit (see below)
           S_IRWXU    00700     mask for file owner permissions
           S_IRUSR    00400     owner has read permission
           S_IWUSR    00200     owner has write permission
           S_IXUSR    00100     owner has execute permission
           S_IRWXG    00070     mask for group permissions
           S_IRGRP    00040     group has read permission
           S_IWGRP    00020     group has write permission
           S_IXGRP    00010     group has execute permission
           S_IRWXO    00007     mask for permissions for others (not in group)
           S_IROTH    00004     others have read permission
           S_IWOTH    00002     others have write permission
           S_IXOTH    00001     others have execute permission


获得链接文件所指向的文件		   
#include <unistd.h>

ssize_t readlink(const char *path, char *buf, size_t bufsiz);



实现ls -l功能
	lstat()		查看符号链接文件自身状态属性 
	getpwuid()	根据用户id获得用户名称
	getgrgid()  根据组id获得组名称
	readlink()	获得链接文件所指向的文件	

	
	
11.文件重定向
touch test.txt

dup() //找到一个空的描述符
dup2	//强制使用选定的描述符
fcntl

12.fcntl函数
