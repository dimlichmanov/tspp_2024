#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main() {

    int a[6][6];
    MPI_Datatype oneslice, twoslice;
    MPI_Aint lb, sz;

    int myrank, ierr;
    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Type_get_extent(MPI_INT, &lb, &sz);

    MPI_Type_vector(3, 1, 2, MPI_INT, &oneslice);
    MPI_Type_commit(&oneslice);

    //MPI_Type_get_extent(oneslice, &lb, &sz);
    //printf("extent row: %d \n", sz);

    MPI_Type_create_hvector(3, 1, 12 * sz, oneslice, &twoslice);
    //MPI_Type_vector(3, 1, 12, oneslice, &twoslice);
    MPI_Type_commit(&twoslice);

    if (myrank == 0) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                a[i][j] = i*6 + j;
            }
        }
        MPI_Send(&a[1][0], 1, twoslice, 1, 0, MPI_COMM_WORLD);
    } else {
        MPI_Recv(&a[1][0], 1, twoslice, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = 5; i >= 0; i--) {
            for (int j = 0; j < 6; j++) {
                printf("%d ", a[i][j]);
            }
            printf("\n");
        }
        
    }
    
    MPI_Type_free(&twoslice);
    MPI_Type_free(&oneslice);
    MPI_Finalize();
}