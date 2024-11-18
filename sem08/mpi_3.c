#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int n = 1000;
    int np, rank;
    int *x = calloc(n, sizeof(x[0]));
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    if (rank == 0) {
        x[0] = 100500;
        x[323] = 42;
    }
    
    // Copy first n entries of x into other processes 

    MPI_Bcast(x, n, MPI_INT, 0, MPI_COMM_WORLD);

    printf("%d/%d: x[0] = %d\n", rank, np, x[0]);
    printf("%d/%d: x[323] = %d\n", rank, np, x[323]);
    
    MPI_Finalize();
    free(x);
    return 0;
}
