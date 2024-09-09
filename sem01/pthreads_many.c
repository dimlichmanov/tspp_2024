
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct tt {
    int a;
    int b;
};

void* func(void* arg) {

    struct tt* my_args = (struct tt*)(arg);

    printf("%d -- %d \n", my_args->a, my_args->b);


}


int main() {

    int n_proc = 4;

    pthread_t my_threads[n_proc];
    struct tt my_params[n_proc];


    for (int i = 0; i < n_proc; i++) {
        my_params[i].a = 0;
        my_params[i].b = i;
        pthread_create(&my_threads[i], NULL, &func, &my_params[i]);
    }


    for (int i = 0; i < n_proc; i++) {
        pthread_join(my_threads[i], NULL);
    }


}