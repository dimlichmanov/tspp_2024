#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int buffer[8][8];
    int recv_buf[8];

    MPI_Init(&argc, &argv);
    int size, my_rank;
    MPI_Aint lb, sz;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Datatype column_type;
    MPI_Type_vector(8, 1, 8, MPI_INT, &column_type);
    //MPI_Type_commit(&column_type);

    MPI_Datatype column_type_new;
    MPI_Type_create_resized(column_type, 0, 1 * sizeof(int), &column_type_new);

    MPI_Type_get_extent(column_type_new, &lb, &sz);
    MPI_Type_commit(&column_type_new);

    if (my_rank == 0) {
        printf("LB: %d, extent: %d\n", lb, sz);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                buffer[i][j] = i * 8 + j;
            }
        }
    }
    else {
       for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                buffer[i][j] = -1;
            }
        }
    }

    MPI_Scatter(buffer, 1, column_type_new, recv_buf, 8, MPI_INT, 0, MPI_COMM_WORLD);

    if (my_rank == 7) {
        for (int j = 0; j < 8; j++) {
            printf("%d ", recv_buf[j]);
        }
    }
    MPI_Type_free(&column_type_new);
    // MPI_Type_free(&column_type);
    MPI_Finalize();
    return EXIT_SUCCESS;
}