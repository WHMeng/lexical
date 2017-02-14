#if 0


--------------------------------------------------------------------------------

int pthread_equal(pthread_t tid1, pthread_t tid2);  // 若相等则返回非零值，否则返回零

pthread_t pthread_self(void);

int pthread_create(pthread_t *restrict tidp, // 若成功则返回 0，否则返回错误编号
                   const pthread_attr_t *restrict attr,
                   void *(*start_rin)(void), void *restrict arg);

-------------------------------------------------------------------------------

单个线程可以通过三种方式退出，在不终止整个进程的情况下停止它的控制流

1）线程只是从启动例程中返回，返回值是线程的退出码
2）线程可以被同一个进程中的其他线程取消
3）线程调用 pthread_exit

void pthread_exit(void *rval_ptr);

int pthread_join(pthread_t thread, void **rval_ptr); // 若成功则返回 0，否则返回错误编号

当一个线程通过调用 pthread_exit 退出或者简单地从启动例程中返回时，进程中的其他线程可以通过调用 pthread_join 函数获得该线程的退出状态

线程可以通过调用 pthread_cancel 函数来请求取消同一进程中的其他线程

int pthread_cancel(pthread_t tid); // 若成功则返回 0，否则返回错误编号，它仅仅是提出请求

线程可以安排它退出时需要调用的函数，即线程清理处理程序，线程可以建立多个清理处理程序

void pthread_cleanup_push(void (*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute);

当线程执行以下动作时调用清理函数，调用参数为 arg，清理函数 rtn 的调用顺序是由 pthread_cleanup_push 函数来安排的

1）调用 pthread_exit 时
2）响应取消请求时
3）用非零 execute 参数调用 pthread_cleanup_pop 时

如果 execute 参数置为 0，清理函数将不被调用，无论哪种情况， pthread_cleanup_pop 都将删除上次 pthread_cleanup_push 调用建立的清理处理程序
这些函数有一个限制，由于它们可以实现宏，所以必须在与线程相同的作用域中以匹配对的形式使用

默认情况下，线程的终止状态会保存到对该线程调用pthread_join，如果线程已经处于分离状态，线程的底层存储资源可以在线程终止时立即被收回。当线程被分离时，并不能用 pthread_join函数等待它的终止状态。对分离状态
的线程进行 pthread_join 的调用会产生失败，返回 EINVAL。pthread_detach 调用可以用于使线程进入分离状态

int pthread_detach(pthread_t tid); // 若成功则返回 0，否则返回错误编号

----------------------------------------------------------------------------------------------------

线程同步
-------------

增量操作

1）从内存单元读入寄存器
2）从寄存器中进行变量值的增加
3）把新的值写回内存单元

互斥变量用 pthread_mutex_t 数据类型来表示，在使用互斥变量以前，必须首先对它进行初始化，可以把它置
为常量 PTHREAD_MUTEX_INITIALIZER（只对静态分配的互斥量）也可以通过调用 pthread_mutex_init 函数进行
初始化。如果动态的分配互斥量（调用 malloc 函数），那么在释放内存前需要调用 pthread_mutex_destroy

int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                       const pthread_mutexattr_t *restrict attr);
					   
int pthread_mutex_destroy(pthread_mutex_t *mutex); // 若成功则返回 0，否则返回错误编号

要用默认的属性初始化互斥量，只需要把 attr 设置为 NULL。

int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex); // 若成功则返回 0，否则返回错误编号

如果线程不希望被阻塞，它可以使用 pthread_mutex_trylock 尝试对互斥量进行加锁。如果调用 pthread_mutex_trylock 时互斥量处于未锁住状态，那么 pthread_mutex_trylock 将锁住互斥量
不会出现阻塞并返回 0，否则 pthread_mutex_trylock 就会失败，不能锁住互斥量，而返回 EBUSY

读写锁 —— 共享-独占锁

1）读模式加锁
2）写模式加锁
3）不加锁

读状态加锁时，所有试图以读模式对它进行加锁的线程都可以得到访问权，但是如果线程希望以写模式对此锁进行加锁，它必须阻塞直到所有线程释放读锁；而此时读写锁通常会阻塞随后的读模式锁请求，这样可以避免读模式锁长期占用，而等待的写模式锁请求一直得不到满足

与互斥量一样，读写锁在使用之前必须初始化，释放它们底层的内存前必须销毁

int pthread_rwlock_init(pthread_rwlock_t *restrict_rwlock,
                        const pthread_rwlockattr_t *restrict_attr);

int pthread_rwlock_destroy(pthread_rwlock_t *rwlock); // 若成功则返回 0，否则返回错误编号

int pthread_rwlock_rdlock(pthread_rwlock_t *rolock); // 读模式加锁
int pthread_rwlock_wrlock(pthread_rwlock_t *rolock); // 写模式加锁
int pthread_rwlock_unlock(pthread_rwlock_t *rolock); // 解锁

int pthread_rwlock_tryrdlock(pthread_rwlock_t *rolock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rolock);

条件变量

pthread_cond_t 数据类型代表条件变量，可以用两种方式初始化，可以把常量 PTHREAD_COND_INITIALIZER 赋给静态分配的条件变量

int pthread_cond_init(pthread_cond_t *restrict_cond,
                      pthread_condattr_t *restrict_attr);

int pthread_cond_destroy(pthread_cond_t *cond); // 若成功则返回 0，否则返回错误编号

使用 pthread_cond_wait 等待条件变为真，如果在给定的时间内条件不能满足，那么会生成一个代表出错码
的返回变量。

int pthread_cond_wait(pthread_cond_t *restrict_cond,
                      pthread_mutex_t *restrict_mutex);

int pthread_cond_timewait(pthread_cond_t *restrict_cond,
                          pthread_mutex_t *restrict_mutex,
						  const struct timespec *restrict_timeout); // 若成功则返回 0，否则返回错误编号
有两个函数可以用于通知线程条件已经满足。pthread_cond_signal 函数将唤醒等待该条件的某个线程，
而 pthread_cond_broadcast 函数将唤醒等待该条件的所有线程。

int pthread_cond_signal(pthread_cond_t *cond);

int pthread_cond_broadcast(pthread_cond_t *cond); // 若成功则返回 0，否则返回错误编号

这个两个函数也称为向线程或条件发送信号。必须注意一定要在改变条件状态以后再给线程发送信号

#endif
