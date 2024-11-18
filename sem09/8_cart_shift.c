#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mpi.h>

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int dims[2] = {0, 0};

    MPI_Dims_create(size, 2, dims);
    int periods[2] = {true, true};
    int reorder = false;
    int coord[2];

    MPI_Comm new_communicator;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &new_communicator);

    enum DIRECTIONS {DOWN, UP, LEFT, RIGHT};
    char* neighbours_names[4] = {"down", "up", "left", "right"};  
    int neighbours_ranks[4];

    MPI_Cart_shift(new_communicator, 0, 1, &neighbours_ranks[DOWN], &neighbours_ranks[UP]);
    MPI_Cart_shift(new_communicator, 1, 1, &neighbours_ranks[LEFT], &neighbours_ranks[RIGHT]);
    
    int my_rank;

    MPI_Comm_rank(new_communicator, &my_rank);

    if (my_rank == 0) {

        MPI_Cart_coords(new_communicator, my_rank, 2, coord);
        printf("I am %d, have coord[0]: %d, coord[1]: %d\n", my_rank, coord[0], coord[1]);

        for (int i = 0; i < 4; i++) {
            if (neighbours_ranks[i] == MPI_PROC_NULL)
                printf("[MPI process %d] I have no %s neighbour.\n", my_rank, neighbours_names[i]);
            else
                printf("[MPI process %d] I have a %s neighbour: process %d.\n", my_rank, neighbours_names[i], neighbours_ranks[i]);
        }
    }
    if (my_rank == 1) {

        MPI_Cart_coords(new_communicator, my_rank, 2, coord);
        printf("I am %d, have coord[0]: %d, coord[1]: %d\n", my_rank, coord[0], coord[1]);

        for (int i = 0; i < 4; i++) {
            if (neighbours_ranks[i] == MPI_PROC_NULL)
                printf("[MPI process %d] I have no %s neighbour.\n", my_rank, neighbours_names[i]);
            else
                printf("[MPI process %d] I have a %s neighbour: process %d.\n", my_rank, neighbours_names[i], neighbours_ranks[i]);
        }
    }
    MPI_Finalize();
    return EXIT_SUCCESS;
}