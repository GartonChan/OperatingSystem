#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define BUFF_SIZE 3
#define PRODUCE_THREAD_SIZE 5
int g_buff[BUFF_SIZE];
int g_write_index = 0;
int g_read_index = 0;

sem_t lock;
sem_t consume_sem, produce_sem;

void *produce(void *ptr){
    int idx = *(int *)ptr;
    printf("in prodece %d %d %d\n", idx, g_write_index, g_read_index);
    while (1){
        sem_wait(&produce_sem);
        
        sem_wait(&lock);
        g_buff[g_write_index] = idx;
        
        sem_post(&lock);
        sem_post(&consume_sem);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t con;
    pthread_t pros[PRODUCE_THREAD_SIZE];
    sem_init(&lock, 0, 1);
    sem_init(&consume_sem, 0, 0);
    sem_init(&produce_sem, 0, BUFF_SIZE);
    
    return 0;
}


// 管程 <- "进程秘书"
// 相关的数据结构和过程(操作) 一并称为管程
// 能被外部并发进程调用
// 共享数据结构 抽象地 表示 系统中的0共享资源.
// 为每个共享资源 设立一个管程, 由用户来编写  --  类似面向对象"的观点

    // 特性: 模块化, 抽象数据类型, 信息掩蔽 
    // 相当于围墙, 将共享变量和操作的若干进程 围了起来
    // 外部只能看到他所提供的接口.
    // 进程要访问临界资源,都需要进入管程申请
    // 归还资源时也需要进入其中调用某些函数.
    // !!  进程 必须 互斥 访问 管程