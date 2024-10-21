#include <stdio.h>
#include <stdbool.h>
#include "omp.h"

int main() {
    #pragma omp parallel
    {
        int orig_id = omp_get_thread_num();
        #pragma omp task if(false) 
        {
            int my_id = omp_get_thread_num();
            printf("Hello, i am %d, originally %d\n", my_id, orig_id);
        }

        //#pragma omp barrier

        // #pragma omp task if(false) 
        // {
        //     int my_id = omp_get_thread_num();
        //     printf("Goodbye, i am %d\n", my_id);
        // }
    }

    return 0;
}