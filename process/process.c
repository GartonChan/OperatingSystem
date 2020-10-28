#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    /* 创建子进程 */
    pid = fork();
    if(pid < 0){  // 创建时发生错误
        fprintf(stderr, "Fork Failed");
        return 1;
    }else if (pid == 0)  // 子进程
        execlp("/bin/ls", "ls" , NULL);
    else{  // 父进程
        wait(NULL);
        printf("Child Complete\n");
    }
    return 0;
}
