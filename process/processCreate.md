
# 系统调用fork()进行子进程创建,可以再不加载新的 可执行映像 的情况下复制进程。
# 进程创建函数fork()和线程创建函数clone()
# 都调用内核函数do_fork(), 主要操作为:
    1. 调用alloc_task_struct()函数获得8kb的task_union内存区,用于存放新进程的PCB和内核栈.
    2. 让当前指针指向父进程的PCB,并把父进程PCB内容拷贝到新分配的新进程的PCB中去(当然PID复制是不可能复制的)
    3. 检查新创建子进程后,当前用户所拥有的进程数目有没有超出给它分配的资源的限制.
    4. 至此,do_fork()已经获得它从父进程能利用的几乎所有的东西:剩下的事情是集中建立子进程的新资源,并让内核知道这个新进程已经呱呱落地.
    5. 子进程状态设置为TASK_UNINTERRUPTIBLE(进入就绪态)保证不会立刻运行.
    6. 调用get_pid()为新进程获取(分配)一个有效的PID !!
    7. 更新 不能从父进程继承的PCB的其他所有域,例如进程间亲属关系的域.
    8. 新的PCB插入进程链表, 保证进程间的亲属关系
    9. 新的PCB插入pidhash哈希表
    10. 子进程PCB中的状态域设置成TASK_RUNNING,并调用wake_up_process()把子进程插入到运行队列链表.
    11. 让父进程和子进程平分剩余的时间片.
    12. 返回子进程的PID.这个PID最终由用户态下的父进程读取.

代码部分解释:
# (1).
    父进程和子进程fork后继续执行
    但fork返回值在两个进程中不同. 
    (新创建进程)子进程返回值为0, 并且子进程的PID返回给了父进程.
# (2).
    关于exec()
        a. 在fork()系统调用后,两个进程中的一个常使用exec()系统调用来用新程序替换进程的内存空间
        b. exec()系统调用将二进制文件加载到内存中(销毁包含exec()系统调用的程序的内存映像并开始执行)
        c. 子进程完全可以不调用exec(),而是作为父进程的副本继续执行.这样,父进程和子进程是运行相同代码的并发进程(子进程是父进程的副本,每个进程都有自己的数据副本)

# (3).
    关于wait() : 
            pid_t pid;
            int status;
            pid = wait(&status);
        a. 父进程使用wait()系统调用等待子进程的完成.
        b. 当子进程执行完毕时(通过隐式或显式调用exit()),父进程从调用wait处继续执行
        c. wait()系统调用传递一个参数,该参数允许父进程获取子进程的退出状态.这个系统调用返还已终止的子进程的PID,以便得知哪些子进程已终止.
        d. 发起wait()后,自己移出就绪队列,直至子进程终止.
        e. 父进程没有调用wait()且终止,子进程会成为孤儿进程
        f. Linux/Unix 通常将init进程作为新的父进程分配给孤儿进程解决此问题.


