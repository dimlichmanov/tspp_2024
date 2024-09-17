#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <bits/pthreadtypes.h>

pthread_mutex_t mutResourceA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutResourceB = PTHREAD_MUTEX_INITIALIZER;

pthread_spinlock_t spinA;
pthread_spinlock_t spinB;


void* foo(void* param) {
    //pthread_mutex_lock(&mutResourceA);
    pthread_spin_lock(&spinA);
    printf("foo acquired resource A\n");

    sleep(1);

    //pthread_mutex_lock(&mutResourceB);
    pthread_spin_lock(&spinB);
    printf("foo acquired resource B\n");
    pthread_mutex_unlock(&mutResourceB);

    pthread_mutex_unlock(&mutResourceA);

    pthread_exit(NULL);
    return NULL;
}

void* bar(void* param) {
    pthread_spin_lock(&spinB);
    //pthread_mutex_lock(&mutResourceB);
    printf("bar acquired resource B\n");

    sleep(1);

    //pthread_mutex_lock(&mutResourceA);
    pthread_spin_lock(&spinA);
    printf("bar acquired resource A\n");
    pthread_mutex_unlock(&mutResourceA);

    pthread_mutex_unlock(&mutResourceB);

    pthread_exit(NULL);
    return NULL;
}



int main() {
    pthread_t tidFoo, tidBar;
    int ret = 0;

    pthread_spin_init(&spinA, PTHREAD_PROCESS_PRIVATE);
    pthread_spin_init(&spinB, PTHREAD_PROCESS_PRIVATE);

    ret = pthread_create(&tidFoo, NULL, &foo, NULL);
    ret = pthread_create(&tidBar, NULL, &bar, NULL);

    ret = pthread_join(tidFoo, NULL);
    ret = pthread_join(tidBar, NULL);

    ret = pthread_mutex_destroy(&mutResourceA);
    ret = pthread_mutex_destroy(&mutResourceB);

    printf("You will never see this statement due to deadlock!");
    return 0;
}