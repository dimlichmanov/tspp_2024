#include <omp.h>
#include <stdio.h>

int main () {

int a = 20; 
#pragma omp parallel firstprivate(a)
{
    #pragma omp single 
    {
        printf("I am %d, Thread amount: %d\n", omp_get_thread_num(), omp_get_num_threads());
    }

    #pragma omp sections
    {
        #pragma omp section
        { 
            //a++;
            printf ("id = %d, a = %d\n", omp_get_thread_num(), a);
        }

        #pragma omp section
        { 
            printf ("id = %d, a = %d \n", omp_get_thread_num(), a);
        }
        
        #pragma omp section
        { 
            printf ("id = %d, a = %d \n", omp_get_thread_num(), a);
        }

        #pragma omp section
        { 
            printf ("id = %d, a = %d \n", omp_get_thread_num(), a);
        }
    }
}
}

