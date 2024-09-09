#include "pthread.h"
#include <assert.h>
#include <stdio.h>

void* my_func() {
    printf("In func\n");
}

int main() {

    pthread_t my_thread;

    pthread_attr_t my_attrs;

    pthread_attr_init(&my_attrs);

    size_t stack_len = __SIZE_MAX__ - 1;

    int err = pthread_attr_setstacksize(&my_attrs, stack_len);

    assert(err == 0);

    err = pthread_create(&my_thread, &my_attrs, &my_func, NULL);

    assert(err == 0);

    pthread_attr_destroy(&my_attrs);

    pthread_exit(NULL);

}