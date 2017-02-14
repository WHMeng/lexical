#if 0


--------------------------------------------------------------------------------

int pthread_equal(pthread_t tid1, pthread_t tid2);  // ������򷵻ط���ֵ�����򷵻���

pthread_t pthread_self(void);

int pthread_create(pthread_t *restrict tidp, // ���ɹ��򷵻� 0�����򷵻ش�����
                   const pthread_attr_t *restrict attr,
                   void *(*start_rin)(void), void *restrict arg);

-------------------------------------------------------------------------------

�����߳̿���ͨ�����ַ�ʽ�˳����ڲ���ֹ�������̵������ֹͣ���Ŀ�����

1���߳�ֻ�Ǵ����������з��أ�����ֵ���̵߳��˳���
2���߳̿��Ա�ͬһ�������е������߳�ȡ��
3���̵߳��� pthread_exit

void pthread_exit(void *rval_ptr);

int pthread_join(pthread_t thread, void **rval_ptr); // ���ɹ��򷵻� 0�����򷵻ش�����

��һ���߳�ͨ������ pthread_exit �˳����߼򵥵ش����������з���ʱ�������е������߳̿���ͨ������ pthread_join ������ø��̵߳��˳�״̬

�߳̿���ͨ������ pthread_cancel ����������ȡ��ͬһ�����е������߳�

int pthread_cancel(pthread_t tid); // ���ɹ��򷵻� 0�����򷵻ش����ţ����������������

�߳̿��԰������˳�ʱ��Ҫ���õĺ��������߳�����������߳̿��Խ���������������

void pthread_cleanup_push(void (*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute);

���߳�ִ�����¶���ʱ���������������ò���Ϊ arg�������� rtn �ĵ���˳������ pthread_cleanup_push ���������ŵ�

1������ pthread_exit ʱ
2����Ӧȡ������ʱ
3���÷��� execute �������� pthread_cleanup_pop ʱ

��� execute ������Ϊ 0�����������������ã�������������� pthread_cleanup_pop ����ɾ���ϴ� pthread_cleanup_push ���ý��������������
��Щ������һ�����ƣ��������ǿ���ʵ�ֺ꣬���Ա��������߳���ͬ������������ƥ��Ե���ʽʹ��

Ĭ������£��̵߳���ֹ״̬�ᱣ�浽�Ը��̵߳���pthread_join������߳��Ѿ����ڷ���״̬���̵߳ĵײ�洢��Դ�������߳���ֹʱ�������ջء����̱߳�����ʱ���������� pthread_join�����ȴ�������ֹ״̬���Է���״̬
���߳̽��� pthread_join �ĵ��û����ʧ�ܣ����� EINVAL��pthread_detach ���ÿ�������ʹ�߳̽������״̬

int pthread_detach(pthread_t tid); // ���ɹ��򷵻� 0�����򷵻ش�����

----------------------------------------------------------------------------------------------------

�߳�ͬ��
-------------

��������

1�����ڴ浥Ԫ����Ĵ���
2���ӼĴ����н��б���ֵ������
3�����µ�ֵд���ڴ浥Ԫ

��������� pthread_mutex_t ������������ʾ����ʹ�û��������ǰ���������ȶ������г�ʼ�������԰�����
Ϊ���� PTHREAD_MUTEX_INITIALIZER��ֻ�Ծ�̬����Ļ�������Ҳ����ͨ������ pthread_mutex_init ��������
��ʼ���������̬�ķ��以���������� malloc ����������ô���ͷ��ڴ�ǰ��Ҫ���� pthread_mutex_destroy

int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                       const pthread_mutexattr_t *restrict attr);
					   
int pthread_mutex_destroy(pthread_mutex_t *mutex); // ���ɹ��򷵻� 0�����򷵻ش�����

Ҫ��Ĭ�ϵ����Գ�ʼ����������ֻ��Ҫ�� attr ����Ϊ NULL��

int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex); // ���ɹ��򷵻� 0�����򷵻ش�����

����̲߳�ϣ����������������ʹ�� pthread_mutex_trylock ���ԶԻ��������м������������ pthread_mutex_trylock ʱ����������δ��ס״̬����ô pthread_mutex_trylock ����ס������
����������������� 0������ pthread_mutex_trylock �ͻ�ʧ�ܣ�������ס�������������� EBUSY

��д�� ���� ����-��ռ��

1����ģʽ����
2��дģʽ����
3��������

��״̬����ʱ��������ͼ�Զ�ģʽ�������м������̶߳����Եõ�����Ȩ����������߳�ϣ����дģʽ�Դ������м���������������ֱ�������߳��ͷŶ���������ʱ��д��ͨ�����������Ķ�ģʽ�������������Ա����ģʽ������ռ�ã����ȴ���дģʽ������һֱ�ò�������

�뻥����һ������д����ʹ��֮ǰ�����ʼ�����ͷ����ǵײ���ڴ�ǰ��������

int pthread_rwlock_init(pthread_rwlock_t *restrict_rwlock,
                        const pthread_rwlockattr_t *restrict_attr);

int pthread_rwlock_destroy(pthread_rwlock_t *rwlock); // ���ɹ��򷵻� 0�����򷵻ش�����

int pthread_rwlock_rdlock(pthread_rwlock_t *rolock); // ��ģʽ����
int pthread_rwlock_wrlock(pthread_rwlock_t *rolock); // дģʽ����
int pthread_rwlock_unlock(pthread_rwlock_t *rolock); // ����

int pthread_rwlock_tryrdlock(pthread_rwlock_t *rolock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rolock);

��������

pthread_cond_t �������ʹ����������������������ַ�ʽ��ʼ�������԰ѳ��� PTHREAD_COND_INITIALIZER ������̬�������������

int pthread_cond_init(pthread_cond_t *restrict_cond,
                      pthread_condattr_t *restrict_attr);

int pthread_cond_destroy(pthread_cond_t *cond); // ���ɹ��򷵻� 0�����򷵻ش�����

ʹ�� pthread_cond_wait �ȴ�������Ϊ�棬����ڸ�����ʱ���������������㣬��ô������һ�����������
�ķ��ر�����

int pthread_cond_wait(pthread_cond_t *restrict_cond,
                      pthread_mutex_t *restrict_mutex);

int pthread_cond_timewait(pthread_cond_t *restrict_cond,
                          pthread_mutex_t *restrict_mutex,
						  const struct timespec *restrict_timeout); // ���ɹ��򷵻� 0�����򷵻ش�����
������������������֪ͨ�߳������Ѿ����㡣pthread_cond_signal ���������ѵȴ���������ĳ���̣߳�
�� pthread_cond_broadcast ���������ѵȴ��������������̡߳�

int pthread_cond_signal(pthread_cond_t *cond);

int pthread_cond_broadcast(pthread_cond_t *cond); // ���ɹ��򷵻� 0�����򷵻ش�����

�����������Ҳ��Ϊ���̻߳����������źš�����ע��һ��Ҫ�ڸı�����״̬�Ժ��ٸ��̷߳����ź�

#endif
