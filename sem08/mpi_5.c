#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    int comm_size, my_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(comm_size != 2)
    {
        printf("This application is meant to be run with 2 processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    if (my_rank == 0) {
        
        int buffer = 323;
        printf("Proc %d sends the value %d.\n", my_rank, buffer);

        // Sync send - we return from this function when receiver (rank 1) has started accepting message and MPI controls it
        // We do not have to write Isend when we receive message through Irecv. Send can be various (Bsend, Ssend, Rsend....)
        MPI_Ssend(&buffer, 1, MPI_INT, (my_rank + 1) % 2, 0, MPI_COMM_WORLD);

    } else {
        int buffer;
        MPI_Request request;

        // We tell MPI that we want to receive such message. Return from that function immediately!  
        MPI_Irecv(&buffer, 1, MPI_INT, (my_rank + 1) % 2, 0, MPI_COMM_WORLD, &request);

        // Do some other stuff, which doesn't require buffer

        // Wait till the data is stored in a buffer
        MPI_Wait(&request, MPI_STATUS_IGNORE);

        printf("Resulting buffer: %d\n", buffer);
    }

    MPI_Finalize();
    return 0;
}
