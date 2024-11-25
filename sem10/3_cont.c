#include "mpi.h"
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int myrank;
    MPI_Status status;
    MPI_Datatype type;

    int buffer[10*10];

    MPI_Init(&argc, &argv);
 
    MPI_Type_contiguous(10, MPI_INT, &type);
    MPI_Type_commit(&type);
 
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
 
    if (myrank == 0)
    {
        for (int i = 0; i < 100; i++) {
            buffer[i] = i;
        }
        
        MPI_Send(buffer + 57, 1, type, 1, 323, MPI_COMM_WORLD);
    }
    else if (myrank == 1)
    {
        MPI_Recv(buffer, 10, MPI_INT, 0, 323, MPI_COMM_WORLD, &status);

        for (int i = 0; i < 10; i++) {
            printf("%d ", buffer[i]);
        }
        printf("\n");
    }

    MPI_Type_free(&type);
 
    MPI_Finalize();
    return 0;
}