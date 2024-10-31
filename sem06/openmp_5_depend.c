#include <stdio.h>
#include <omp.h>

int main() {
    int number;

    #pragma omp parallel
    #pragma omp single nowait
    {
        #pragma omp task depend(out:number)
        number = 5;

        #pragma omp task depend(inout:number)
        {
            int my_id = omp_get_thread_num();
            printf("I am thread %d and I think the number is %d\n", my_id, number);
            number++;
        }

        //Barrier inside work-sharing directives is not allowed
        //#pragma omp barrier

        #pragma omp task depend(in:number)
        {
            int my_id = omp_get_thread_num();
            printf("I am thread %d and I think the final number is %d\n", my_id, number);
        }
    }

    return 0;
}