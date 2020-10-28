#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 15

int value = 0;
void *increase(void *threadid)
{
    long tid;
    tid = (long)threadid;
    printf("Increase value, thread #%ld! ", tid);
    value+=1;
    printf("value now is %d\n", value);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
	printf("The global value is initialized as %d\n", value);
    for (t=0; t<NUM_THREADS; t++){
        printf("In main: creating thread #%ld\n", t);
        rc = pthread_create(&threads[t], NULL, increase, (void *)t);
        if (rc){
            printf("Error: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    for (t=0; t<NUM_THREADS; t++){
        pthread_join(threads[t], NULL);
    }
    printf("\nvalue ends as %d\n", value);
    // last thing that main() should do
    pthread_exit(NULL);
    return 0;
}
