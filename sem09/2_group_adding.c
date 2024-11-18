#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    MPI_Init(NULL, NULL);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);

    int n = 7;
    const int ranks[7] = {1, 2, 3, 5, 7, 11, 13};

    MPI_Group prime_group;
    MPI_Group_incl(world_group, 7, ranks, &prime_group);

    MPI_Comm prime_comm;
    MPI_Comm_create_group(MPI_COMM_WORLD, prime_group, 0, &prime_comm);

    int prime_rank = -1, prime_size = -1;
    
    if (MPI_COMM_NULL != prime_comm) {
        MPI_Comm_rank(prime_comm, &prime_rank);
        MPI_Comm_size(prime_comm, &prime_size);
    }

    printf("WORLD RANK/SIZE: %d/%d --- PRIME RANK/SIZE: %d/%d\n",
    world_rank, world_size, prime_rank, prime_size);

    MPI_Group_free(&world_group);
    MPI_Group_free(&prime_group);

    if (MPI_COMM_NULL != prime_comm) {
    MPI_Comm_free(&prime_comm);
    }

    MPI_Finalize();
}