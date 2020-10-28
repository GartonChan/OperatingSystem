#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int shareddata = 5;

int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();  // 父进程和子进程fork后继续执行
    // 但fork返回值在两个进程中不同. 
    // (新创建进程)子进程返回值为0, 并且子进程的PID返回给了父进程.
    if (pid < 0){
        printf("error\n\n");
        _exit(-1);
    }else if (pid == 0){
        shareddata = shareddata + 1;  // 子进程对拷贝的shareddata副本加1
        printf("child process\n");
        execlp("/bin/ls", "ls", NULL);  
        /*
                    关于exec()
            在fork()系统调用后,两个进程中的一个常使用exec()系统调用来用新程序替换进程的内存空间
            exec()系统调用将二进制文件加载到内存中(销毁包含exec()系统调用的程序的内存映像并开始执行) 
         */  
    }else {
        wait(NULL); 
        printf("parent process\n");
        printf("shareddata %d\n", shareddata);  // 父进程处的shareddata值应为5
        _exit(-1);  // 调用exit来终止进程(释放数据结构,保留PID)
        /*
                    关于wait() : 
                pid_t pid;
                int status;
                pid = wait(&status);
            父进程使用wait()系统调用等待子进程的完成.
            当子进程执行完毕时(通过隐式或显式调用exit()),父进程从调用wait处继续执行
            wait()系统调用传递一个参数, 该参数允许父进程获取子进程的退出状态.
        这个系统调用返还已终止的子进程的PID,以便得知哪些子进程已终止.
         */
    }
    return 0;
}
