#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

char str[64] = "";
sem_t sem;
void *runner(void *thread)
{
    sem_wait(&sem);
    printf("hello child\n");
    printf("%s\n", str);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t thread;
    int rc;
    long t;
    sem_init(&sem, 0, 0);
    rc = pthread_create(&thread, NULL, runner, (void *)t);
    if (rc)
    {
        printf("ERROR;return code from pthread_create() is %d\n", rc);
        exit(-1);
    }
    scanf("%s", str);
    sem_post(&sem);
    pthread_join(thread, NULL);
    printf("Parent hello\n");
    pthread_exit(NULL);
    return 0;
}
