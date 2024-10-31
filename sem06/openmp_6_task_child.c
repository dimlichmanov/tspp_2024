#include <stdio.h>
#include "omp.h"

int main() {
    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp task
        {
            int my_id = omp_get_thread_num();
            printf("I am parent %d \n", my_id);

            #pragma omp task 
            {
                int child_id = omp_get_thread_num();
                printf("I am child %d \n", child_id);
            }

            //#pragma omp taskwait

            printf("Hi from parent %d \n", my_id);
        }
        
        #pragma omp taskwait

        printf("Hej from producer %d\n", omp_get_thread_num());
    }
    return 0;
}