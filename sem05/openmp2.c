#include <stdio.h>
#include <omp.h>
int main (void)
{
    omp_set_nested(1);
    omp_set_dynamic(0);

    printf ("Before: num_thds=%d\n", omp_get_num_threads());

    omp_set_num_threads(4);

    int i = 0;

#pragma omp parallel
{
    
    #pragma omp single
    {
        printf ("Inner: num_thds=%d\n", omp_get_num_threads());
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            printf ("Inner Inner : num_thds=%d\n", omp_get_num_threads());
        }
    }

    // #pragma omp barrier
    
    // omp_set_nested(0);

    // #pragma omp parallel
    // {
    //     #pragma omp single
    //     {
    //         printf ("Inner: num_thds=%d\n", omp_get_num_threads());
    //     }
    // }
    // #pragma omp barrier

    // #pragma omp single
    // {
    //     /*
    //     S-44 * If OMP_NUM_THREADS=2,3 was set, the following should print:
    //     S-45 * Outer: num_thds=2
    //     S-46 */
    //     printf ("Outer: num_thds=%d\n", omp_get_num_threads());
    // }   
}
    return 0;
}