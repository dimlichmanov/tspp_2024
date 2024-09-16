#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mut;   
//pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;   
int counter = 0;

void* doTask(void* param) {
    //sleep(1);

    pthread_mutex_lock(&mut);

    for (int i = 0; i < 1000; ++i)
        ++counter;

    pthread_mutex_unlock(&mut);

    pthread_exit(NULL);
    return NULL;
}

int main() {
    const int NUM_THREADS = 16;
    pthread_t lstTid[NUM_THREADS];
    int ret = 0;

    pthread_mutex_init(&mut, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        ret = pthread_create(&lstTid[i], NULL, &doTask, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        ret = pthread_join(lstTid[i], NULL);
    }
    
    ret = pthread_mutex_destroy(&mut);

    printf("%d\n", counter);
    return 0;
}