#include <mpi.h>
#include <stdio.h>

/* Allreduce example. Note that "count" (and other params) should be similar on each process (count = rank is incorrect!) */

int main(int argc, char** argv) {
    int size, rank, tag, count; 
    int x=0,y = 0;
    MPI_Status stat; 
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    count=size;
    x=1; 

    MPI_Allreduce (&x, &y, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD); 

    printf(" %d \n", y); 
    
    MPI_Finalize();
}

