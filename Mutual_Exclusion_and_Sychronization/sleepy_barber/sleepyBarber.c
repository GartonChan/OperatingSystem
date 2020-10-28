/*
    无人进店 -> 理发师瞌睡
    有人进店  -> 理发椅空闲 -> 等待理发师来理发 (同步)
            -> 理发椅有人 -> 等待区椅子入座
                        -> 等待区已满 -> 离开理发店

    同步体现在: 坐在理发椅的顾客等待理发师理发                           
    互斥体现在: 等待区椅子有限,且只有顾客能坐, 顾客只能等理发师理发
 */

#define CHAIRS 5 // 为等待的顾客准备的座椅数

typedef int semaphore;
semaphore customers = 0;  // 等候的顾客数
semaphore barbers = 0;  // 空闲的理发师数
semaphore mutex = 1;  // 互斥保证临界区操作
int waiting = 0;  // 为等待理发顾客坐的椅子数

void barber()
{
    while (1){
        P(customers);  // 没有顾客(customers lock)就打瞌睡
        P(mutex);  // 互斥进入临界区
        waiting--;  // 如果有顾客意味着椅子数目必>=1, 这里让等待理发顾客椅子数目-1
        V(barbers); // 理发师醒来准备理发了
        V(mutex);  //  ???
        cut_hair();  // 理发
    }
}

void customer()
{
    P(mutex);  //
    if(waiting < CHAIRS){
        waiting++;  // 等待的顾客数目+1
        V(customers);  // 等待顾客 -> 与barber 构成同步
        V(mutex);  //
        P(barbers);  // 申请理发师, 理发师在忙则等待
        get_haircut();
    }else{
        V(mutex);  // 直接离开
    }
}