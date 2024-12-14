#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int comm_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

    int window_buffer = 0;
    MPI_Win win;
    
    MPI_Win_create(&window_buffer, sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);

    if(comm_rank == 0)
    {
        printf("Value in my window_buffer before MPI_Accumulate: %d.\n", window_buffer);
    }

    MPI_Win_fence(0, win);

    if (comm_rank > 0)
    {
        MPI_Accumulate(&comm_rank, 1, MPI_INT, 0, 0, 1, MPI_INT, MPI_SUM, win);
    }

    MPI_Win_fence(0, win);

    if(comm_rank == 0)
    {
        printf("Value in my window_buffer after MPI_Accumulate: %d.\n", window_buffer);
    }

    MPI_Win_free(&win);
    MPI_Finalize();

    return 0;
}