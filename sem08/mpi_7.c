#include <stdlib.h>
#include <mpi.h>
#include <stdio.h>

int main() {

    MPI_Init(NULL, NULL);
    int comm_size,*sendbuf;
    int root = 0, rbuf[100], i, *displs, *scounts;
    int stride = 2;
    int comm_rank;

    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);


    if (comm_rank == root) {
        sendbuf = (int*)malloc(400 * sizeof(int));
        for (int i = 0; i < 400; i++) {
            sendbuf[i] = i;
        }
    }

    displs = (int*)malloc(comm_size*sizeof(int));
    scounts = (int*)malloc(comm_size*sizeof(int));

    for (i=0; i<comm_size; ++i) {
        displs[i] = (comm_size - 1 - i) * 100; //invert the order 
        scounts[i] = 100; 
    }
    
    //  to 3        to 2           to 1           to 0  
    // 0 1 ... | 100 101 ... | 200 201 ...  | 300 .. 301 ... 399

    MPI_Scatterv(sendbuf, scounts, displs, MPI_INT, rbuf, 100, MPI_INT, root, MPI_COMM_WORLD);

    printf("Rank %d got value rbuf[0] = %d\n",  comm_rank, rbuf[0]);

    MPI_Finalize();

    if (comm_rank == root) {
        free(sendbuf);
    }

}
