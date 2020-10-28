#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(int argc, char const *argv[])
{
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;
    /*  Create a pipe  */
    if(pipe(fd) == -1){
        fprintf(stderr, "Pipe filed");
        return 1;
    }
    /*  fork a child process  */
    pid = fork();
    if (pid < 0){
        fprintf(stderr, "Fork failed");
        return 1;
    }
    if (pid > 0){
        // parent process
        close(fd[READ_END]);  // close the unused end of pipe
        write(fd[WRITE_END], write_msg, strlen(write_msg)+1);  // write to the pipe
        close(fd[WRITE_END]);  // close the write end of the pipe
    }
    else{
        // child process
        close(fd[WRITE_END]);
        read(fd[READ_END], read_msg, BUFFER_SIZE);  // read from the pipe
        printf("read: %s\n", read_msg);
        close(fd[READ_END]);
    }
    return 0;
}
