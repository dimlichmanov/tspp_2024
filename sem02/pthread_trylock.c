#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

void* doTask(void* param) {
    int ret = 0;
    sleep(1);

    printf("I am thread %d\n", (int)pthread_self());
    ret = pthread_mutex_trylock(&mut);

    if (ret) {
        pthread_exit(NULL);
        return NULL;
    }
    printf("I am thread %d\n", (int)pthread_self());
    for (int i = 0; i < 1000000; ++i)
        ++counter;

    pthread_mutex_unlock(&mut);

    pthread_exit(NULL);
    return NULL;
}



int main() {
    int NUM_THREADS = 3;
    pthread_t lstTid[NUM_THREADS];
    int ret = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        ret = pthread_create(&lstTid[i], NULL, &doTask, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        ret = pthread_join(lstTid[i], NULL);
    }

    printf("counter = %d\n", counter);
    // counter can be 10000, 20000 or 30000

    ret = pthread_mutex_destroy(&mut);
    return 0;
}