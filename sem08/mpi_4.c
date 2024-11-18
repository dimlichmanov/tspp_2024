#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int np, rank;
    int x = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    x = rank + 1;
    // if we do not want to introduce additional buffers 
    // 1 + 2 + 3 + 4 if rank = 10
    
    MPI_Allreduce(MPI_IN_PLACE, &x, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("rank %d: x = %d\n", rank, x);

    MPI_Finalize();
    return 0;
}
