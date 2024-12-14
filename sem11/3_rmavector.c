#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARR_LEN 2 

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int comm_size, comm_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    MPI_Datatype column_type;
    MPI_Type_vector(8, 1, 8, MPI_INT, &column_type);
    MPI_Type_commit(&column_type);
    
    int window_buffer[ARR_LEN];

    int matrix[64];
    int window_length = 0;

    if (comm_rank == 1)
    {
        for (int i = 0; i < 64; i++) {
            matrix[i] = i;
        }
        window_length = 64;
    }

    MPI_Win win;

    MPI_Win_create(matrix, window_length * sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);

    MPI_Win_fence(0, win);

    int remote_vector[8];
    
    if (comm_rank == 0)
    {
        MPI_Get(&remote_vector, 8, MPI_INT, 1, 5, 1, column_type, win);
    }

    MPI_Win_fence(0, win);

    if (comm_rank == 0)
    {
        for (int i = 0; i < 8; i++) {
            printf("%d\n", remote_vector[i]);
        }
    }

    MPI_Win_free(&win);
    MPI_Finalize();

    return 0;
}