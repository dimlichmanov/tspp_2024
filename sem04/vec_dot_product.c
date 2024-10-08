#include <stdio.h>
#include <immintrin.h>
#include <math.h>
#include <stdint.h>
#include "omp.h"

const int N = 1024 * 1024 * 128;

double slow_dot_product(const double *a, const double *b) {
  double answer = 0.0;

#pragma GCC novector
  for(int idx = 0; idx < N; idx++)
    answer += a[idx]*b[idx];
  return answer;
}

double reduce(__m256d input) {
  __m256d temp = _mm256_hadd_pd(input, input);
  return ((double*)&temp)[0] + ((double*)&temp)[2];
}

double dot_product(const double *a, const double *b) {
    __m256d sum_vec = _mm256_set_pd(0.0, 0.0, 0.0, 0.0);

    for(int idx = 0; idx < N/4; idx++) {
        __m256d x = _mm256_load_pd(a+4*idx);
        __m256d y = _mm256_load_pd(b+4*idx);
        __m256d z = _mm256_mul_pd(x,y);

        sum_vec = _mm256_add_pd(sum_vec, z);
    }

    double final = 0.0;

    for(int idx = N-N%4; idx < N; idx++) {
        final += a[idx] * b[idx];
    }

    __attribute__ ((aligned (32))) double red[4];

    _mm256_store_pd(red, sum_vec);

    return final + red[3] + red[2] + red[1] + red[0];
}

int main() {

    double* a = (double*) _mm_malloc(N * sizeof(double), 32);
    double* b = (double*) _mm_malloc(N * sizeof(double), 32);

    //__attribute__ ((aligned (32))) double a[N], b[N];

    for(int i = 0; i < N; i++) {
        a[i] = b[i] = 0.001;
    }

    double time_c = omp_get_wtime();
    double slow_answer = slow_dot_product(a,b);
    double time_d = omp_get_wtime();
    printf("%lf\n", slow_answer);
    printf("Time : %lf\n", time_d - time_c);

    for(int i = 0; i < N; i++) {
        a[i] = b[i] = 0.002;
    }
    
    double time_a = omp_get_wtime();
    double answer = dot_product(a, b);
    double time_b = omp_get_wtime();
    printf("%lf\n", answer);
    printf("Time : %lf\n", time_b - time_a);
}