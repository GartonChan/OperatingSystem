typedef int Item;
typedef int semaphore;

// 假定Buffer中的数据类型为Item
#define buffer_size 20
Item Buffer[buffer_size];
Item data_p1, data_p2;   // 用于写入和读取时暂存数据 
semaphore empty = buffer_size;
semaphore full = 0;
semaphore mutex = 1;
int i=0, j=0;

void P1()
{   
    while (1){
        //     ...    前序操作, 并且将写入Buffer的外部数据先暂存于data_p1中
        P(empty);
        P(mutex);
        Buffer[i] = data_p1;
        i = (i+1) % buffer_size;
        V(mutex);
        V(full);
    }
}



void P2()
{
    while (1){
        P(full);
        P(mutex);
        data_p2 = Buffer[j];  // 取出数据暂存于data_c
        j = (j+1) % buffer_size;
        V(mutex);
        V(empty);
        // 输出data_p2的数据
    }
}