#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int share_value = 0;
sem_t sem;
void *runner1(void *thread_id)
{
    sem_wait(&sem);
    while (share_value < 20)
    {
        if(share_value % 2 == 0)
            printf("thread1:%d\n", share_value);
        share_value++;
    }
    sem_post(&sem);
    pthread_exit(NULL);
}

void *runner2(void *thread_id)
{
    sem_wait(&sem);
    while (share_value < 20)
    {
        if(share_value % 3 == 0)
            printf("thread2:%d\n", share_value);
        share_value++;
    }
    sem_post(&sem);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t thread1, thread2;
    int rc;
    long t;
    sem_init(&sem, 0, 1);
    rc = pthread_create(&thread1, NULL, runner1, (void *)t);
    if(rc){
        printf("ERROR;return code from pthread_create() is %d\n", rc);
        exit(-1);
    }
    rc = pthread_create(&thread2, NULL, runner2, (void *)t);
    if(rc){
        printf("ERROR;return code from pthread_create() is %d\n", rc);
        exit(-1);
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Parent hello\n");
    pthread_exit(NULL);
    return 0;
}

