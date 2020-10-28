/*
    生产者/消费者问题, 又称为有界缓冲区问题
        -> 生产者将数据放入到缓冲区(至少有一个单元是空的), 生产者之间是互斥的.
        -> 消费者将数据从缓冲区取走(至少有一个单元是满的), 消费者之间是互斥的.
            并且同一时刻只能由一个进程操作缓冲区.
        生产者和消费者之间是同步关系.
    下面用信号量(条件变量)来解决这个问题.
        
        >> 伪代码 <<
 */

#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

#define buffer_size 10
#define n 10

typedef int Item;

Item buffer[buffer_size];

sem_t full;
sem_t empty; // = buffer_size;
sem_t mutex;
int i, j;  // 用于计数
Item buffer[buffer_size];  // 缓冲区
Item data_p, data_c;  // 数据

void producer()
{
    while (1){
        // produce an item in data_p (生产产品)
        P(empty);  // 占用一个空位(非满)
        P(mutex);  // 申请访问,占用互斥信号量
        buffer[i] = data_p;  // 存入产品到缓冲区
        i = (i+1) % n;
        V(mutex);  // 释放互斥信号量
        V(full);  // 和empty相对,表明增加了一个产品
    }
    
}

void consumer()
{
    while (1){
        P(full);  // 申请得到一个产品(非空)
        P(mutex);  // 申请访问,占用互斥信号量
        data_c = buffer[j];  // 从缓冲区取出产品
        j = (j+1) % n;
        V(mutex);  // 释放互斥信号量
        V(empty);  // 腾出了一个空位以供生产
        // consume the item in data_c (使用产品)
    }
    
}