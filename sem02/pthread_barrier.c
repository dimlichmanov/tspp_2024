#include <unistd.h>
#include <pthread.h>
#include <stdio.h>


pthread_barrier_t syncPointA;
pthread_barrier_t syncPointB;

int waitTime = 4;

void* processRequest(void* argVoid) {
    sleep(waitTime);

    printf("I am %d\n", (int)pthread_self());
    fflush(stdout);
    pthread_barrier_wait(&syncPointA);

    printf("I am %d\n", (int)pthread_self());
    fflush(stdout);
    pthread_barrier_wait(&syncPointB);


    pthread_exit(NULL);
    return NULL;
}



int main() {
    int NUM_THREADS = 4;
    pthread_t lstTid[NUM_THREADS];
    int ret = 0;

    ret = pthread_barrier_init(&syncPointA, NULL, 2);
    ret = pthread_barrier_init(&syncPointB, NULL, 2);

    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_create(&lstTid[i], NULL, &processRequest, NULL);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        ret = pthread_join(lstTid[i], NULL);
    }

    ret = pthread_barrier_destroy(&syncPointA);
    ret = pthread_barrier_destroy(&syncPointB);
    return 0;
}