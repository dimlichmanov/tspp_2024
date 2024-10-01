#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include <time.h>

void
generate_array(double *a, int size)
{
    int i;
    for (i = 0; i < size; ++i) {
        a[i] = (double) rand();
    }
}

double
array_sum(double *a, int size)
{
    int i;
    double res = 0.0;
    for (i = 0; i < size; ++i) {
        res += a[i];
    }
    return res;
}

int
main(int argc, char **argv)
{
    double *array = NULL, sum;
    int n = 10, retval;

    float rtime, ptime, mflops;
    long long flpops;

    array = calloc(n, sizeof(array[0]));
    if (!array) {
        fputs("memory allocation error!\n", stderr);
        return 1;
    }

    srand(323);

    retval = PAPI_flops_rate(PAPI_DP_OPS, &rtime, &ptime,
                             &flpops, &mflops);
    if (retval != PAPI_OK) {
        fputs("failed to start measuring\n", stderr);
        free(array);
        return 1;
    }
    
    generate_array(array, n);
    sum = array_sum(array, n);

    retval = PAPI_flops_rate(PAPI_DP_OPS, &rtime, &ptime,
                             &flpops, &mflops);
    if (retval != PAPI_OK) {
        fputs("failed to stop measuring\n", stderr);
        free(array);
        return 1;
    }

    printf("sum = %f\n", sum);
    printf("real time = %f\n"
           "process time = %f\n"
           "floating point operations = %lld\n"
           "mflops = %f\n",
           rtime, ptime, flpops, mflops);


    free(array);
    
    return 0;
}