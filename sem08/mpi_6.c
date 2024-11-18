#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    int comm_size, my_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        for (int i = 0; i < 100; i++ ) {
            int buffer = 100 + i;
            printf("Proc %d sends the value %d.\n", my_rank, buffer);
            MPI_Send(&buffer, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
        }
    }
    if (my_rank == 1) {
        for (int i = 0; i < 100; i++ ) {
            int buffer = 200 + i;
            printf("Proc %d sends the value %d.\n", my_rank, buffer);
            MPI_Send(&buffer, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
        }
    }

    if (my_rank == 2) {
        int buffer1;
        int buffer2;
        MPI_Request request1;
        MPI_Request request2;
        for (int i = 0; i < 100; i++ ) {
            MPI_Irecv(&buffer1, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request1);
            MPI_Irecv(&buffer2, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request2);

            // We need to wait on request to pass to the next iteration! 
            MPI_Wait(&request1, MPI_STATUS_IGNORE);
            MPI_Wait(&request2, MPI_STATUS_IGNORE);
        }

        printf("Resulting buffer1: %d\n", buffer1);
        printf("Resulting buffer2: %d\n", buffer2);
    }

    MPI_Finalize();
    return 0;
}
