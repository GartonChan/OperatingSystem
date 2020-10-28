#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum;  // 线程可以共享的数据

void *runner(void *param);  // 线程调用的函数
int main(int argc, char const *argv[])
{
    pthread_t tid;  // thread identifier，线程控制符
    pthread_attr_t attr;  // 定义线程属性
    if (argc != 2){
        fprintf(stderr, "Usage:create_thread <integer value>\n");
        return -1;
    }
    if (atoi(argv[1]) < 0){ 
        fprintf(stderr, "%d must be >= 0\n", atoi(argv[1])); 
        return -1;
    }
    pthread_attr_init(&attr);  // 初始化线程属性
    pthread_create(&tid, &attr, runner, argv[1]);  // 创建线程
    pthread_join(tid, NULL);  // 等待子线程执行完成
    printf("sum = %d\n", sum);
    return 0;
}

void *runner(void *param)
{
    int i, upper = atoi(param);  // atoi(param) 即对param进行ascii to integer的转换
    sum = 0;
    for (i=0; i<=upper; i++)
        sum+=i;
    pthread_exit(0);  // 线程终止
}
