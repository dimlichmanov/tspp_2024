#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int np, rank;
    printf("Hello before Init! \n"); 

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    printf("%d/%d, hello\n", rank, np);
    
    MPI_Finalize();
    return 0;
}
