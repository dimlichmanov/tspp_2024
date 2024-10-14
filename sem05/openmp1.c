#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){

#pragma omp parallel 
{
    int local = 0;
    #pragma for
    for (int i = 0; i < 16; i++){
        printf("Hello from process:  %d\n", omp_get_thread_num());
    }
}
    return 0;
}
