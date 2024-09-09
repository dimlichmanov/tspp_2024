#define _GNU_SOURCE
#include <assert.h>
#include <sched.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_affinity() {
    cpu_set_t mask;
    long nproc, i;

    if (sched_getaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
        perror("sched_getaffinity");
        assert(false);
    }

    nproc = sysconf(_SC_NPROCESSORS_ONLN);
    printf("sched_getaffinity = ");
    for (i = 0; i < nproc; i++) {
        printf("%d ", CPU_ISSET(i, &mask));
    }
    printf("\n");
}

int main(void) {
    cpu_set_t mask;

    cpu_set_t old_mask;
    cpu_set_t new_mask;

    print_affinity();
    printf("sched_getcpu = %d\n", sched_getcpu());
    CPU_ZERO(&mask);
    CPU_SET(2, &mask);
    CPU_SET(3, &mask);

    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) == -1) {
         perror("sched_setaffinity");
         assert(false);
    }

    print_affinity();
    // /* TODO is it guaranteed to have taken effect already? Always worked on my tests. */
    printf("sched_getcpu = %d\n", sched_getcpu());
    // return EXIT_SUCCESS;
}
