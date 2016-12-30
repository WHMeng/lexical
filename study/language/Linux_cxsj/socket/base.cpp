#if 0

#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol);

套接字地址
------------

AF_UNIX 域套接字来说，它的地址由结构 sockaddr_un 来描述

#include <sys/un.h>
struct sockaddr_un {
	sa_family_t sun_family; // AF_UNIX
	char        sun_path[]; // pathname
};

AF_INET 域套接字来说，它的地址由结构 sockaddr_in 来描述

#include <netinet/in.h>
struct sockaddr_in {
	short int          sin_family; // AF_INET
	unsigned short int sin_port; // Port number
	struct in_addr     sin_addr; // Internet address
};

// IP address
struct in_addr {
	unsigned long int s_addr;
};

命名套接字
----------

#include <sys/socket.h>
int bind(int socket, const struct sockaddr *address, size_t address_len);

创建套接字队列
----------------

#include <sys/socket.h>
int listen(int socket, int backlog); // 成功时返回 0，失败时返回 -1

接受连接
---------

#include <sys/socket.h>
int accept(int socket, struct sockaddr *address, size_t *address_len);

请求连接
--------

#include <sys/socket.h>
int connect(int socket, const struct sockaddr *address, size_t address_len);

NIS(网络信息服务或黄页服务), DNS(域名服务)
--------------------------------------------

#include <netdb.h>
struct hostent *gethostbyaddr(const void *addr, size_t len, int type);
struct hostent *gethostbyname(const char *name);

struct hostent {
	char *h_name; // name of the host
	char **h_aliases;
	int h_addrtype; // address type
	int h_length; // length in bytes of the address
	char **h_addr_list // list of address (network order)
};

#include <netdb.h>
struct servent *getservbyname(const char *name, const char *proto);
struct servent *getservbyport(int port, const char *proto);

struct servent {
	char *s_name; // name of the service
	char **s_aliases;
	int s_port; // the IP port number
	char *s_proto; // the service type, usually "tcp" or "udp"
};

#include <arpa/inet.h>
char *inet_ntoa(struct in_addr in); // 将一个因特网主机地址转换为一个点分四元组格式的字符串，失败时返回 -1

#include <unistd.h>
int gethostname(char *name, int namelength);

套接字选项
------------

#include <sys/socket.h>
int setsockopt(int socket, int level, int option_name,
		       const void *option_value, size_t option_len);

--------------------------------------------------------------------------------------------

select 系统调用允许程序同时在多个底层文件描述符上等待输入的到达(或输出的完成)，也即服务器
可以通过同时在多个打开的套接字上等待请求到来的方法处理多个客户

select 函数对数据结构 fd_set 进行操作，它是由打开的文件描述符构成的集合。有一组定义好的
宏可以用来控制这些集合

#include <sys/types.h>

void FD_ZERO(fd_set *fdset);
void FD_CLR(int fd, fd_set *fdset);
void FD_SET(int fd, fd_set *fdset);
int FD_ISSET(int fd, fd_set *fdset);

select 函数还可以用一个超时值来防止无限期的阻塞
-----------------------------------------------

#include <sys/time.h>
#include <sys/types.h>

struct timeval {
	time_t tv_sec;
	long   tv_usec;
};

int select(int nfds, fd_set *readfds, fd_set *writefds,
		   fd_set *errorfds, struct timeval *timeout);
// 返回状态发生改变的描述符总数。失败时返回 -1

select 调用用于测试文件描述符集合中，是否有一个文件描述符已处于可读或可写或出错状态，它将阻塞以等
待某个文件描述符进入上述这些状态


sendto 系统调用从 buffer 缓存区中给使用指定套接字地址的目标服务器发送一个数据报
--------------------------------------------------------------------------------

int sendto(int sockfd, void *buffer, size_t len, int flags,
		   struct sockaddr *to, socklen_t tolen);

recvfrom 系统调用在套接字上等待从特定地址到来的数据报，并将它放入 buffer 缓存区
--------------------------------------------------------------------------------

int recvfrom(int sockfd, void *buffer, size_t len, int flags,
			 struct sockaddr *from, socklen_t fromlen);



#endif
