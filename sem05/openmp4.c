#include <omp.h>
#include <stdio.h> 
#include <unistd.h>

int main() {
#pragma omp parallel 
{

    int thread_id = omp_get_thread_num();

#pragma omp for nowait
    for (int i = 0; i < 4; i++) {
        if (thread_id == 1) {
            sleep(5);
        }
    }

#pragma omp for 
    for (int i = 0; i < 4; i++) {
        printf("I am finished %d \n", thread_id);
    }

}
}