#include<mpi.h>
#include<stdio.h>


int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Comm comm;
    int dim[2], period[2], reorder;
    int coord[2], id;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    dim[0]=4; dim[1]=3;

    period[0]=1; period[1]=0;
    
    reorder=0;

    MPI_Cart_create(MPI_COMM_WORLD, 2, dim, period, reorder, &comm);

    int new_rank;

    MPI_Comm_rank(comm, &new_rank);

    if (rank == 5)
    {
        MPI_Cart_coords(comm, rank, 2, coord);
        printf("Rank %d (old rank is %d) coordinates are %d %d\n", new_rank, rank, coord[0], coord[1]);
    }

    if(rank==0)
    {
        coord[0]=3; coord[1]=1;
        MPI_Cart_rank(comm, coord, &id);
        printf("The processor at position (%d, %d) has rank %d\n", coord[0], coord[1], id);
    }

    MPI_Finalize();
    return 0;
}