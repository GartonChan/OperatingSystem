#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define TRUE 1
#define FALSE 0
#define N 2  //进程数
int turn;  // 哪一个进程有权进入临界区
int flag[N] = {FALSE, FALSE};  // 申请进入临界区的标志

// 首先必须明确的是: 在peterson算法中, 
// 被限制为两个进程在临界区和剩余区之间交替执行

void enter_region(int process);
void leave_region(int process);
void process_0();
void process_1();

int main(int argc, char const *argv[])
{
    process_0();
    process_1();
    process_0();
    process_0();
    process_1();
    return 0;
}


void enter_region(int process)
{
    /*  process发起申请,请求进入临界区  */
    int other;  // 另一个进程
    other = 1-process;
    turn = other;   // 谦让另一个进程, 让其先进入
    flag[process] = TRUE;
    while(flag[other]==TRUE && turn==other){  // 判断临界区是否被另一进程所访问, -> 忙则等待
        printf("do nothing, just waiting\n");  /* do nothing, just waiting */
    }
    printf("Visiting critical section\n");
}

void leave_region(int process)
{
    /*  process退出临界区,将自己的flag设置为FALSE  */
    flag[process] = FALSE;
}

void process_0()
{
    enter_region(0);
    // 临界区
    printf("I am process 0 \n");
    printf("0 -> Critical section\n\n");
    leave_region(0);
    // 剩余区
}

void process_1()
{
    enter_region(1);
    // 临界区
    printf("I am process 1 \n");
    printf("1 -> Critical section\n\n");
    leave_region(1);
    // 剩余区
}