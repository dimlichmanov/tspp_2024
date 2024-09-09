#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void* my_func() {
    printf("Hello from thread\n");
    char* retval = (char*) malloc(10);
    strcpy(retval, "1234567890");
    pthread_exit((void*)(retval));
}



int main() {
    pthread_t my_thread;
    void* val_from_thread;
    pthread_create(&my_thread, NULL, &my_func, NULL);
    pthread_join(my_thread, &val_from_thread);

    printf("%s\n", (char*)val_from_thread);



}