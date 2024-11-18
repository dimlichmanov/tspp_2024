#include "mpi.h" 
#include <stdio.h> 
#include <stdlib.h> 

/* The same error can be made in Scatter! */
int main (int argc, char *argv[]) { 
    int size, rank, tag, count, i, root; 
    int x[100],y[100]; 

    MPI_Status stat;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    count=rank;
    root = 1; 

    if (rank==root) {
        for (i=0; i< size * 2; i++) {
            x[i] = i * size;
        }
    }
    // | to 0 |  to 1 |  to 2 |  to 3 |
    // | 0  4 | 8  12 | 16 20 | 24 28 |  if rank == 4

    MPI_Scatter(x, 2, MPI_INT, y, 2, MPI_INT, root, MPI_COMM_WORLD); 
    
    if (rank== size - 1) printf(" %d \n",y[0]);
    
    MPI_Finalize(); 
}