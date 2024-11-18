#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
 
    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);
 
    MPI_Group group_a;
    int group_a_processes[2] = {0, 2};
    MPI_Group_incl(world_group, 2, group_a_processes, &group_a);
 
    MPI_Group group_b;
    int group_b_processes[2] = {2, 3};
    MPI_Group_incl(world_group, 2, group_b_processes, &group_b);
 
    MPI_Group intersection_group;
    MPI_Group_intersection(group_a, group_b, &intersection_group);
 
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
    MPI_Comm new_communicator;
    MPI_Comm_create(MPI_COMM_WORLD, intersection_group, &new_communicator);
    
    if(new_communicator == MPI_COMM_NULL)
    {
        printf("Process %d is not part of the intersection group.\n", my_rank);
    }
    else
    {
        printf("Process %d is part of the intersection group.\n", my_rank);
    }
 
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}