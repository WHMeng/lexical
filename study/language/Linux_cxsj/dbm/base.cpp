#if 0

ndbm / gdbm

#include <ndbm.h>
编译行选项 -I/usr/include/gdbm
编译行选项 -lgdbm

如果不起作用
#include <gdbm-ndbm.h>
编译行选项 -I/usr/include/gdbm
编译行选项 -lgdbm_compat -lgdbm

-------------------------------------------

#include <ndbm.h>

datum 数据类型
void *dptr;
size_t dsize

打开一个 dbm 数据库时，通常会创建两个物理文件：.pag 和 .dir 后缀，并返回一个
dbm 指针用来访问这两个文件，这两个文件不能被直接读写

-----------------------------------------------------------------------------

DBM *dbm_open(const char *filename, int file_open_flags, mode_t file_mode);
int dbm_store(DBM *database_descriptor, datum key, datum content, int store_mode);
datum dbm_fetch(DBM *database_descriptor, datum key);
void dbm_close(DBM *database_descriptor);

dbm_open
打开已有数据库，也可以创建数据库，其余参数与 open 函数的第二第三个参数一样

dbm_store
吧数据存储到数据库中，两个 datum 参数，一个用于引用索引，一个用于实际数据。最后
一个参数用于控制试图以一个已有关键字来存储数据时会发生的情况；如果被设置为
dbm_insert，存储操作将失败并返回 -1，如果被设置为 dbm_replace，则新数据将覆盖
已有数据并且 dbm_store 返回 0；当发生其他错误时，dbm_store 返回一个负值

dbm_fetch
从数据库中检索数据

-----------------------------------------------------------------------------------------

int dbm_delete(DBM *database_descriptor, datum key); // 成功时返回 0
int dbm_error(DBM *database_descriptor); // 测试数据库中是否有错误发生，没有就返回 0
int dbm_clearerr(DBM *database_descriptor); // 清除数据库中所有已被置位的错误条件标志
datum dbm_firstkey(DBM *database_descriptor);
datum dbm_nextkey(DBM *database_descriptor);

DBM *db_ptr;
datum key;

for(key = dbm_firstkey(db_ptr); key.dptr; key = dbm_nextkey(db_ptr));

#endif
