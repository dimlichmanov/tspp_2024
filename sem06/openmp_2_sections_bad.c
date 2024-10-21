#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int fib(int n)
{
	int i, j;
	if (n < 2)
		return n;
	else
	{
#pragma omp parallel sections 		
{
    #pragma omp section 
    {
        i = fib(n - 1);
    }
    #pragma omp section 
    {
        j = fib(n - 2);
    }
}
    printf("Current int %d is on thread %d \n", i + j, omp_get_thread_num());
    return i + j;
	}
}

int main()
{
	int n = 20;

#pragma omp parallel shared(n) 	
    {
    #pragma omp single 		
    {
			printf("%d\n", omp_get_num_threads());
			printf("fib(%d) = %d\n", n, fib(n));
    }
}
}