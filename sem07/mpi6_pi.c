#include "mpi.h"
#include <math.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int done = 0, myid, numprocs, i;
    double PI_math_lib = M_PI;
    double mypi, pi, h, sum, x;
    int n = 100000;

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
   
	h   = 1.0 / (double) n;
	sum = 0.0;
	for (i = myid + 1; i <= n; i += numprocs) {
	    x = h * ((double)i - 0.5);
	    sum += 4.0 / (1.0 + x*x);
	}
	mypi = h * sum;
    
	MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
		   MPI_COMM_WORLD);
    
	if (myid == 0) {
	    printf("pi is approximately %.16f, Error is %.16f\n",
		   pi, fabs(pi - PI_math_lib));
    }
    MPI_Finalize();
    return 0;
}