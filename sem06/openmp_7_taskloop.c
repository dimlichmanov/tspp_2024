#include "omp.h"
#include <stdlib.h>
#include <stdio.h>

double dotprod(int n, double *x, double *y) {
    double r = 0.0; 
    #pragma omp parallel
    {
        // #pragma omp single 
        // {
        #pragma omp taskloop reduction(+: r) 
        for (int i = 0; i < n; i++) {
            r += x[i] * y[i];
        }
        //}
    }
    return r;
}

int main () {

    int N = 1000000;

    double* x_arr = (double*)malloc(N*sizeof(double));
    double* y_arr = (double*)malloc(N*sizeof(double));
    srand(omp_get_wtime());
    for (int q = 0; q < N; q++) {
       x_arr[q] = (double)rand()/RAND_MAX; 
       y_arr[q] = (double)rand()/RAND_MAX; 
    }

    double res_seq = 0.0;

    for (int q = 0; q < N; q++) {
        res_seq += x_arr[q] * y_arr[q];
    }

    double res_par = dotprod(N, x_arr, y_arr);

    printf("Res seq : %lf\n", res_seq);
    printf("Res par : %lf\n", res_par);

    free(x_arr);
    free(y_arr);
}