#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int value = 5;  // globalValue

int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();  // fork a child process
    if (pid < 0){
        fprintf(stderr, "Fork Failed.");
        return 1;
    }else if (pid == 0){
        value += 15;
        printf("child pid:%d, value=%d\n", getpid(), value);
        }else{
            wait(NULL);
            printf("parent pid:%d, value=%d\n", getpid(), value);
        }
    
    return 0;
}
