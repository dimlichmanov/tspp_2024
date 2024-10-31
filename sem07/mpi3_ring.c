#include <stdio.h>
#include "mpi.h"

int main( argc, argv )
int argc;
char **argv;
{
    int rank, value, size;
    MPI_Status status;

    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &size );
	
    if (rank == 0) {
        value = 5;
        MPI_Send( &value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD );
    }
	else
    {
        value = 9;
	    MPI_Recv( &value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, 
		      &status );
	    if (rank < size - 1) { 
            MPI_Send( &value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD );
        }
	}

	printf( "Process %d got %d\n", rank, value );

    MPI_Finalize();
    return 0;
}