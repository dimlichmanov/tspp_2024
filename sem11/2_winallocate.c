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

    int* window_buffer;
    MPI_Win win;

    MPI_Win_allocate(ARR_LEN * sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &window_buffer, &win);
    
    if (comm_rank == 1)
    {
        window_buffer[1] = 323;
    }

    MPI_Win_fence(0, win);

    int remote_value;
    
    if (comm_rank == 0)
    {
        MPI_Get(&remote_value, 1, MPI_INT, 1, 1, 1, MPI_INT, win);

        int my_value = 42;
        MPI_Put(&my_value, 1, MPI_INT, 1, 0, 1, MPI_INT, win);
    }

    MPI_Win_fence(0, win);

    if (comm_rank == 0)
    {
        printf("MPI_Get from proc 1: %d.\n", remote_value);
    }
    else
    {
        printf("MPI_Put from proc 0 : %d.\n", window_buffer[0]);
    }

    MPI_Win_free(&win);

    MPI_Finalize();

    return EXIT_SUCCESS;
}