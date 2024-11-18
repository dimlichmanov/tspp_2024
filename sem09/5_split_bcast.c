#include "mpi.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int myid, numprocs;
    int color, new_id, new_nodes;
    MPI_Comm New_Comm;
    int broad_val = -1;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    
    color = myid%2;
    
    MPI_Comm_split(MPI_COMM_WORLD, color, myid, &New_Comm);

    MPI_Comm_rank(New_Comm, &new_id);
    MPI_Comm_size( New_Comm, &new_nodes);
    
    if (new_id == 0) broad_val = color;
    
    MPI_Bcast(&broad_val, 1, MPI_INT, 0, New_Comm);

    printf("Old proc %d has new rank %d and received value %d\n", myid, new_id, broad_val);
    MPI_Finalize();
}