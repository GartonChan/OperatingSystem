/*
    举例如:
        读取数据库的进程
        更新数据库的进程
    
    读取: 不会修改数据  -> 读者之间相互无影响
    更新: 因为修改数据  -> 写者之间和写者和读者之间都会相互影响.

    -> 我们要求 写者在写入时, 对共享数据具有独占访问权.
        这种同步问题被称作 :  读者写者问题
        它又有几个不同变种, 都与读写的优先级有关.
            1. 第一类: 要求除非写者已获得使用共享对象的权限,否则读者不会一直等待 -> 同步
            2. 第二类: 一旦一个写者准备就绪, 这个写者就必须尽快完成写操作.(写优先级高)
 
        在读者 多于 写者的程序中, 因为读写锁的建立通常比信号量或互斥锁需要更多的开销.
        允许多个读取器增加的并行性弥补了设置读写器锁所涉及的开销.

 */

#include <semaphore.h>
#include <stdio.h>

sem_t Wmutex;  // 互斥信号量
sem_t Rmutex;
int Rcount = 0;

void reader()
{
    while (1){
        P(Rmutex);  // 读者锁
        // 这里先锁定读者所是需要检查写者锁有无锁定 ( 根据后面可知 没有读者即Rcount==0时 写者锁是可获得的. )
        if(Rcount == 0) 
            P(Wmutex);  // 占用写者的互斥量, 不能写入
        Rcount += 1;  // 读者+1
        V(Rmutex); // unlock, 让下一个读者也可以进行读取.
        // read (执行读操作)
        P(Rmutex);  // 占用读者的互斥量, 不再读取.
        Rcount -= 1;  // 读者-1
        if(Rcount == 0)  // 如果没有其他人读, 则将写者锁打开unlock
            V(Wmutex);  // 这时, 如果没人读的情况下, 就可以让写者写入.
        V(Rmutex);  // 解开读者锁, 以供下次读取.
    }  // P V 操作一定成对出现 
}

void writer()  
{  // 只有一个互斥, 相比读者进程简单.
    while (1){
        P(Wmutex);
        // write (执行写操作)
        V(Wmutex);
    }
}
