#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include <stdint.h>
#include <assert.h>

void
handle_error(int retval, const char *str)
{
    if (retval != PAPI_OK) {
        fprintf(stderr,
                "%s: PAPI error %d: %s\n",
                str, retval, PAPI_strerror(retval));
        exit(1);
    }
}

void
gen_matrix(int32_t *a, int32_t n)
{
    int32_t n2 = n * n;
    int32_t i;

    for (i = 0; i < n2; ++i) {
        a[i] = rand();
    }
}

void
matrix_mul(int32_t *a, int32_t *b, int32_t *c, int32_t n)
{
    int32_t i, j, k;
    for (i = 0; i < n; ++i) {
        for (k = 0; k < n; ++k) {
            for (j = 0; j < n; ++j) {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
}


int
main(int argc, char **argv)
{
    int event_set = PAPI_NULL, retval;
    long long values[2];

    int n = 1000;
    
    int32_t *a = calloc(n * n, sizeof(a[0]));
    int32_t *b = calloc(n * n, sizeof(b[0]));
    int32_t *c = calloc(n * n, sizeof(c[0]));

    assert(a != NULL && b != NULL && c != NULL);

    gen_matrix(a, n);
    gen_matrix(b, n);
    
    retval = PAPI_library_init(PAPI_VER_CURRENT);

    if (retval != PAPI_VER_CURRENT) {
        fprintf(stderr, "PAPI library init error!\n");
        exit(1);
    }

    handle_error(PAPI_create_eventset(&event_set), "create eventset");

    handle_error(PAPI_add_event(event_set, PAPI_L1_DCM), "add PAPI_L1_DCM");
    handle_error(PAPI_add_event(event_set, PAPI_L2_DCM), "add PAPI_L2_DCM");
    

    handle_error(PAPI_start(event_set), "papi start");

    matrix_mul(a, b, c, n);
    
    handle_error(PAPI_stop(event_set, values), "papi stop");

    printf("PAPI_L1_DCM = %lld\n"
           "PAPI_L2_DCM = %lld\n",
           values[0],
           values[1]);


    handle_error(PAPI_cleanup_eventset(event_set), "cleanup eventSet");
    handle_error(PAPI_destroy_eventset(&event_set), "destroy eventset");

    free(a);
    free(b);
    free(c);
    
    return 0;
}