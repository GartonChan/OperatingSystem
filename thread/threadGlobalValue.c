#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <wait.h>

int value = 0;
void *runner(void *p)
{
    value = 5;
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    pthread_t thread;
    int rc;
    pid = fork();  // fork a child process
    if (pid < 0){
        fprintf(stderr, "Fork Failed.");
        return 1;
    }else if (pid == 0){
        pthread_create(&thread, NULL, runner, NULL);
        pthread_join(thread, NULL);
        printf("child value:%d\n", value);
    }else{
        wait(NULL);
        printf("Parent value:%d\n", value);
    }
    return 0;
}
