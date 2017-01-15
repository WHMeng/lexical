#if 0

非阻塞 I/O、记录锁、系统 V 流机制、I/O 多路转接、readv 和 writev 函数、存储映射 I/O

以上都称为高级 I/O

------------------------------------------------------------------------------------

非阻塞 I/O
-----------

对于一个给定的描述符有两种方法对其指定非阻塞 I/O

1）如果调用 open 获得描述符，则可指定 O_NONBLOCK 标志（3.3节）
2）对于一个已经打开的描述符，则可调用 fcntl，由该函数打开 O_NONBLOCK 文件
   状态标志（见3.4节）

记录锁（字节范围锁头）
---------------------

当一个进程正在读或则修改文件的某个部分时，它可以阻止其他进程修改同一文件区
... 待更新

STREAMS
---------

I/O 多路转接
---------------

#include <sys/select.h>

int select(int maxfdpl, fd_set *readfds,
		fd_set *writefds, fd_set *exceptfds, struct timeval *tvptr);

返回值：准备就绪的描述符数，若超时则返回 0，若出错则返回 -1

struct timeval {
	long tv_sec;
	long tv_usec;
}

tvptr == NULL // 永远等待，直到捕捉到一个信号或中断此无限期等待
tvptr->tv_sec == 0 && tvptr->tv_usec == 0 // 完全不等待，测试完所有指定的描述符并立即返回
tvptr->fv_sec != 0 || tvptr->tv_usec != 0

int FD_ISSET(int fd, fd_set *fdset);
int FD_CLR(int fd, fd_set *fdset);
int FD_SET(int fd, fd_set *fdset);
int FD_ZERO(fd_set *fdset);

#include <poll.h>

int poll(struct pollfd fdarray[], nfds_t nfds, int timeout);

返回值：准备就绪的描述符数，若超时则返回 0，若出错则返回 -1

struct pollfd {
	int fd;
	short events; // events of interest on fd
	short revents; // events that occurred on fd
}

#endif
