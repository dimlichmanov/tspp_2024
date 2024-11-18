#include <mpi.h>
#include <stdio.h>


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int comm_rank;
    MPI_Group g;
    int g_size;
    int g_rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);
    
    MPI_Comm_group(MPI_COMM_WORLD, &g);

    MPI_Group_size(g, &g_size);
    MPI_Group_rank(g, &g_rank);

    printf("Group size: %d, my rank in group: %d, in COMM_WORLD: %d\n", g_size, g_rank, comm_rank);

    MPI_Finalize();
}