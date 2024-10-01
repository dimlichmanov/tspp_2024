#include <stdio.h>
#include <stdlib.h>
#include <papi.h>
#include <time.h>

void generate_array(double *a, int size)
{
    int i;
    for (i = 0; i < size; ++i) {
        a[i] = (double) rand();
    }
}

double array_sum(double *a, int size)
{
    int i;
    double res = 0.0;
    for (i = 0; i < size; ++i) {
        res += a[i];
    }
    return res;
}

int main(int argc, char **argv)
{
    int retval, EventSet = PAPI_NULL;
    int EventCode;
    long long cm;

    /* Initizalize library */
    retval = PAPI_library_init(PAPI_VER_CURRENT);
    if (retval != PAPI_VER_CURRENT) {
        printf("PAPI library init error!\n");
        exit(1);
    }

    /* Convert to integer */
    retval = PAPI_event_name_to_code("ix86arch::UNHALTED_CORE_CYCLES", &EventCode);
    if ( retval != PAPI_OK) {
        printf("PAPI_event_name_to_code error %d \n", retval);
    }

    if (PAPI_query_event(EventCode) != PAPI_OK) {
        printf("Can not measure %d event ", EventCode);
    } else {
        printf("Will be succeeded in measuring %d event ", EventCode);
    }

    /* Create the EventSet */
    if (PAPI_create_eventset(&EventSet) != PAPI_OK) {
        printf("PAPI_create_eventset error!\n");
        exit(1);
    }

    /* Add Total Instructions Executed to our EventSet */
    if (PAPI_add_event(EventSet, EventCode) != PAPI_OK) {
        printf("PAPI_add_event error !\n");
        exit(1);
    }

    unsigned int native = 0x0;
    PAPI_event_info_t info;

    if (PAPI_get_event_info(EventCode, &info) != PAPI_OK) {
        printf("Error in get event_info\n");
        exit(1);
    }

    printf("\n%d, %s, count: %s\n", info.event_code, info.symbol, info.short_descr);

    double *array = NULL, sum;
    int n = 1024 * 1024;

    float rtime, ptime, mflops;
    long long flpops;

    array = calloc(n, sizeof(array[0]));
    if (!array) {
        fputs("memory allocation error!\n", stderr);
        return 1;
    }

    srand(323);

    retval = PAPI_start(EventSet);
    if (retval != PAPI_OK) {
        fputs("failed to start measuring\n", stderr);
        free(array);
        return 1;
    }
    
    generate_array(array, n);
    sum = array_sum(array, n);

    retval = PAPI_stop(EventSet, &cm);
    
    if (retval != PAPI_OK) {
        fputs("failed to stop measuring\n", stderr);
        free(array);
        return 1;
    }

    printf("sum = %f\n", sum);
    printf("cm = %lld\n", cm);

    free(array);
    
    return 0;
}