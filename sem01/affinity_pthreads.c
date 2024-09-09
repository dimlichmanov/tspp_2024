//compilation: gcc -o affinity affinity.c -lpthread

#define _GNU_SOURCE
#include <sched.h>   //cpu_set_t , CPU_SET
#include <pthread.h> //pthread_t
#include <stdio.h>

void *th_func(void * arg); 

int main(void) {
  pthread_t thread0; //the thread
  pthread_t thread1; //the thread


  //we can set one or more bits here, each one representing a single CPU
  cpu_set_t cpuset; 

  CPU_ZERO(&cpuset);       //clears the cpuset
  CPU_SET( 3 , &cpuset); //set CPU 2 on cpuset
  CPU_SET( 7 , &cpuset); //set CPU 2 on cpuset
  sched_setaffinity(0, sizeof(cpuset), &cpuset);

  pthread_create(&thread0,NULL,th_func,NULL); 
  pthread_create(&thread1,NULL,th_func,NULL); 

  pthread_join(thread0,NULL);   
  pthread_join(thread1,NULL); 

  pthread_exit(NULL);

  return 0;
}


void *th_func(void * arg)
{  
  while (1);
       ; 

  return 0;
}
