#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    int size, rank;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Status status;
    
    char message_my[30];
    char message_other[30];
    if (rank == 0) { 
        strcpy(message_my, "Created by rank 0");
        MPI_Sendrecv(message_my, 30, MPI_CHAR, 1, 0, message_other, 30, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }else if (rank == 1) { 
        strcpy(message_my, "Created by rank 1");
        MPI_Sendrecv(message_my, 30, MPI_CHAR, 0, 0, message_other, 30, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } 
    
    printf( "I am rank %d, got from other: %s\n", rank, message_other);
    MPI_Finalize();

}