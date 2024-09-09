#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

void *
thread_func(void *ignored_argument)
{
    int s;

    s = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

    printf("%s(): started; cancelation disabled\n", __func__);
    sleep(5);
    printf("%s(): about to enable cancelation\n", __func__);

    s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    sleep(1000);    

    printf("%s(): not canceled!\n", __func__);
    return NULL;
}

int
main(void)
{
    pthread_t thr;
    void *res;
    int s;

    s = pthread_create(&thr, NULL, &thread_func, NULL);

    sleep(2);     

    printf("%s(): sending cancelation request\n", __func__);
    s = pthread_cancel(thr);

    s = pthread_join(thr, &res);

    assert(res == PTHREAD_CANCELED);
}