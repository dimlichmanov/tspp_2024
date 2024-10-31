#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Status status;

    if (size == 2) {
        if (rank == 0) {
            int x = 323;
            int* a = (int*) malloc(323 * sizeof(int));
            for (int i = 0; i < 323; i++) {
                a[i] = i;
            }
            MPI_Ssend(&x, 1, MPI_INT, 1, 90, MPI_COMM_WORLD);
            MPI_Ssend(a, 323, MPI_INT, 1, 99, MPI_COMM_WORLD);
            free(a);
        } else {
            int y = 0;
            int* b = (int*) malloc(323 * sizeof(int));
            MPI_Recv(b, 323, MPI_INT, 0, 99, MPI_COMM_WORLD, &status);
            MPI_Recv(&y, 1, MPI_INT, 0, 90, MPI_COMM_WORLD, &status);
            printf("y = %d\n", y);
            for (int i = 0; i < 323; i++) {
                printf("%d ", b[i]);
            }
            printf("\n\n%d, %d, %d\n", status.MPI_SOURCE, status.MPI_TAG, status.MPI_ERROR);
        }
    }
    
    MPI_Finalize();
    return 0;
}
