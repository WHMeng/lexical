#if 0

处理机调度的主要目的：分配处理机

调度级别
---------

高级调度：也叫作业调度

中级调度：涉及外存，特别是应用于虚拟存储技术，目的是提高内存利用率
          和系统吞吐量

低级调度：也叫进程调度


性能评价标准
-------------

1. CPU 利用率
2. 吞吐量：单位时间 CPU 完成作业的数量
3. 周转时间：从作业提交到作业完成的时间间隔
   Ti = t_ci - t_si
   带权周转时间 W = T/R，R 为实际运行时间
4. 就绪等待时间
5. 响应时间

常用调度算法
-------------

1. 先来先服务 (FCFS)，长作业有利，CPU 繁忙型有利，I/O 繁忙型不利
2. 短作业优先 (SJF)，短作业有利，为类提高系统吞吐量，降低作业平均等待时间
3. 优先级法
   静态优先级：会产生饥饿现象
   动态优先级：为了解决饥饿现象
4. 时间片轮转法 (RR)
   时间片太长：退化为 FCFS
   时间片太短：CPU 切换频繁

中断处理
---------

1. 保存现场
2. 分析原因
3. 处理中断
4. 中断返回

shell 基本工作原理
-------------------

1. 读取用户由键盘输入的命令行
2. 分析命令，以命令名作为文件名，并将其他参数改造为系统调用 execve() 内部
   处理所要求的形式
3. 终端进程调用 fork() 建立一个子进程
4. 终端进程本身用系统调用 wait4() 来等待子进程完成(如果是后台命令，则不
   等待)。当子进程运行时调用 execve()，子进程根据文件名(即命令名)到目录中
   查找有关文件(这是命令解释程序构成的文件),将它调入内存，执行这个程序(解
   释这条命令)
5. 如果命令末尾有 & 号，则终端进程不用系统调用 wait4() 等待，立即发提示符，
   让用户输入下一个命令，转到第一步。否则，终端进程要一直等待，当子进程
   完成处理后终止，向父进程报告，此时终端进程醒来，在做必要判别等工作后
   终端进程发提示符

#endif
