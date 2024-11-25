#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

     MPI_Datatype column_type;
        MPI_Type_vector(8, 1, 8, MPI_INT, &column_type);
        //MPI_Type_create_hvector(8, 1, 8*sizeof(int), MPI_INT, &column_type);
        MPI_Type_commit(&column_type);

    if (my_rank == 0) {
        int buffer[64];
        for (int i = 0; i < 64; i++) {
            buffer[i] = i;
        }
        MPI_Send(&buffer[5], 1, column_type, 1, 0, MPI_COMM_WORLD);

    } else {
        int received[64];
        MPI_Recv(&received, 1, column_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < 64; i++) {
            printf("%d ", received[i]);
        }
        printf("\n");
    }
    
    MPI_Finalize();
    return EXIT_SUCCESS;
}