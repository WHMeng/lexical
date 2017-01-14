#if 0

使用 C 语言连接 mysql 数据库

1）初始化一个连接句柄结构
2）实际进行连接

#include <mysql.h>

MYSQL *mysql_init(MYSQL *); // 初始化

MYSQL *mysql_real_connect(MYSQL *connection,
		const char *server_host, // 既可以是主机名，也可以时 IP 地址
		const char *sql_user_name,
		const char *sql_password,
		const char *db_name,
		unsigned int port_number, // 0
		const char *unix_socket_name, // NULL
		unsigned int flags);

程序退出时

void mysql_close(MYSQL *connection);

设置选项（可在 mysql_init 和 mysql_close 之间多次使用）

int mysql_options(MYSQL *connection, enum option_to_set, const char *argument); // 成功返回 0

常用选项

enum                               argument                           说明
MYSQL_OPT_CONNECT_TIMOUT           const unsigned int *               连接超时之前的等待秒数
MYSQL_OPT_COMPRESS                 None, 使用 NULL                    网络连接中使用压缩机制
MYSQL_INIT_COMMAND                 const char *                       每次连接建立后发送的命令

例如：设置连接超时为 7 秒

unsigned int timeout = 7;
...
connection = mysql_init(NULL);
ret = mysql_options(connection, MYSQL_OPT_CONNECT_TIMEOUT, (const char *)&timeout);
if(ret){
	// Handle error
	...
}

connection = mysql_real_connect(connection ...

---------------------------------------------------------------------------------------------------

编译

gcc -I/usr/include/mysql xx.c -L/usr/lib64/mysql -lmysqlclient -o xx // 不同系统具体情况不同

错误处理

unsigned int mysql_erron(MYSQL *connection); // 返回错误码
char *mysql_error(MYSQL *connection); // 返回错误文本信息

-----------------------------------------------------------------------------

执行 SQL 语句

int mysql_query(MYSQL *connection, const char *query) // 如果成功则返回 0

my_ulonglong mysql_affected_rows(MYSQL *connection); // 返回受之前执行的 UPDATE、INSERT、DELETE 查询影响的行数

当使用 printf 时推荐使用 %lu 格式

--------------------------------------------------------------------------------------------------

被设置为 AUTO_INCREMENT 类型的列，一旦你插入一行，你如何知道刚插入的孩子被分配了什么数字？

mysql 以函数 LAST_INSERT_ID() 的形式提供一个专门的解决方案
mysql 会基于每个用户对最后分配的值进行跟踪

INSERT INTO children(fname, age) VALUES('Tom', 13);
SELECT LAST_INSERT_ID();

--------------------------------------------------------------------------------------

C 应用程序中提取数据一般需要 4 个步骤
1）执行查询
2）提取数据
3）处理数据
4）必要的清理工作

一次提取所有数据的函数
MYSQL_RES *mysql_store_result(MYSQL *connection);

在 mysql_store_result 调用成功之后，你需要调用 mysql_num_rows 来得到返回记录的数目
my_ulonglong mysql_num_rows(MYSQL_RES *result); // 如果没有返回行，这个值将是 0

MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);
从 mysql_store_result 的结果结构中提取一行，并把它放到一个行结构中。当数据用完或发生错误时返回 NULL

void mysql_data_seek(MYSQL_RES *result, my_ulonglong offset);
用来在结果集中进行跳转，第二个参数是一个行号

MYSQL_ROW_OFFSET mysql_row_tell(MYSQL_RES *result);
返回一个偏移值，用来表示结果集中的当前位置

MYSQL_ROW_OFFSET mysql_row_seek(MYSQL_RES *result, MYSQL_ROW_OFFSET offset);
这将在结果集中移动当前位置，并返回之前的位置。使用了 mysql_row_tell 的返回值

void mysql_free_result(MYSQL_RES *result);
清理内存

一次提取一行数据
MYSQL_RES *mysql_use_result(MYSQL *connection);

-----------------------------------------------------------------------------------------

处理返回的数据

unsigned int mysql_field_count(MYSQL *connection);
提供了一些关于查询结果的基本信息，它接受连接对象，并返回结果集中的列数目

MYSQL_FIELD *mysql_fetch_field(MYSQL_RES *result);
将元数据和数据提取到一个新的结构中

MYSQL_FIELD_OFFSET mysql_field_seek(MYSQL_RES *result, MYSQL_FIELD_OFFSET offset);
覆盖当前的字段编号，该编号会随每次 mysql_fetch_field 调用而自动增加。如果给参数
offset 传递 0，你将跳回第一列


#endif
