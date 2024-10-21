#include <stdio.h>
#include "omp.h"
#include <stdbool.h>

int main() {

    int n = 1; 

    #pragma omp parallel
    {
        int my_id = omp_get_thread_num();
    
        #pragma omp single
        {
        #pragma omp task
        {
            int task_id = omp_get_thread_num();
            printf("Hello world from thread originally %d, de-facto %d\n", my_id, task_id);
        } 

        
        }
        //printf("i am thread %d!\n", my_id);
        //}
    }
    return 0;
}