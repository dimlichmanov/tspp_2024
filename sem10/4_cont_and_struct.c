#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
 
struct person_t
{
    int age;
    double height;
    char name[10];
};

int main(int argc, char *argv[])
{
    int my_rank = 0;
    MPI_Status status;
    MPI_Datatype cont_pers_type;

    printf("%d\n", offsetof(struct person_t, height));

    MPI_Init(&argc, &argv);

    MPI_Datatype person_type;
    int lengths[3] = {1, 1, 10};

    MPI_Aint displacements[3];
    struct person_t dummy_person;
    MPI_Aint base_address;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Get_address(&dummy_person, &base_address);
    MPI_Get_address(&dummy_person.age, &displacements[0]);
    MPI_Get_address(&dummy_person.height, &displacements[1]);
    MPI_Get_address(&dummy_person.name, &displacements[2]);

    if (my_rank == 0) {
        printf("%d --- %d ----- %d\n",  displacements[0], displacements[1], displacements[2]);
    }

    displacements[0] = MPI_Aint_diff(displacements[0], base_address);
    displacements[1] = MPI_Aint_diff(displacements[1], base_address);
    displacements[2] = MPI_Aint_diff(displacements[2], base_address);

    if (my_rank == 0) {
        printf("%d --- %d ----- %d\n",  displacements[0], displacements[1], displacements[2]);
    }

    MPI_Datatype types[3] = {MPI_INT, MPI_DOUBLE, MPI_CHAR};

    MPI_Type_create_struct(3, lengths, displacements, types, &person_type);
    MPI_Type_commit(&person_type);

    MPI_Type_contiguous(10, person_type, &cont_pers_type);
    MPI_Type_commit(&cont_pers_type);

    if (my_rank == 0)
    {
        struct person_t people[10];
        for (int i = 0; i < 10; i++) {
            people[i].age = 20 + i;
            strncpy(people[i].name, "Tom", 9);
            people[i].name[9] = '\0';
            people[i].name[0] = 'A' + 2*i;
            people[i].height = 160 + i;
        }
        
        MPI_Send(people, 1, cont_pers_type, 1, 323, MPI_COMM_WORLD);
    }
    else if (my_rank == 1)
    {
        struct person_t people[10];
        printf("Pers size: %d\n", sizeof(struct person_t));

        MPI_Recv(people, 1, cont_pers_type, 0, 323, MPI_COMM_WORLD, &status);

        MPI_Aint pers_extent;
        MPI_Aint lb;
        int pers_size;

        MPI_Type_size(cont_pers_type, &pers_size);
        MPI_Type_get_extent(cont_pers_type, &lb, &pers_extent);
        
        printf("Pers size: %d, extent: %d, lower bound: %d, sizeof(): %d \n\n", pers_size, pers_extent, lb, sizeof(people));

        for (int i = 0; i < 10; i++) {
            printf("Age: %d, Height: %lf, Name: %s \n", people[i].age, people[i].height, people[i].name);
        }

        printf("\n");
    }

    MPI_Type_free(&person_type);
    MPI_Type_free(&cont_pers_type);
 
    MPI_Finalize();
    return 0;
}