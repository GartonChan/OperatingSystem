#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(int argc, char const *argv[])
{
    char write_msg[BUFFER_SIZE] = "Hello!\n";
    char read_msg[BUFFER_SIZE];
    int fd[2];  // (file descriptor) 文件描述符
    pid_t pid;  // 创建进程
    if (pipe(fd) == -1){  // pipe()调用,建立管道
        fprintf(stderr, "Pipe Failed.\n");
        return 1;
    }
    pid = fork();  // fork()调用
    if (pid < 0){           // fork发生错误
        fprintf(stderr, "Fork Failed.\n");
        return 1;
    }else if (pid > 0){     // 父进程
        // 写入到管道里
        close(fd[READ_END]);
        write(fd[WRITE_END], write_msg, strlen(write_msg)+1);
        close(fd[WRITE_END]);
    }else{                  // 子进程
        // 从管道中读取
        close(fd[WRITE_END]);
        read(fd[READ_END], read_msg, BUFFER_SIZE);
        printf("Read: %s\n", read_msg);
        close(fd[READ_END]);
    }
    return 0;
}
