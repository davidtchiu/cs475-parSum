#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "rtclock.h"

#define N 1000000000
#define NUM_THREADS 4

/** globals (shared) */
long partial_sums[NUM_THREADS]; // to hold outputs from threads

/** struct to hold parameters to partialSum() **/
typedef struct thread_args
{
  int tid;    // the given thread id (0, 1, ...)
  long begin; // where to begin summation
  long end;   // where to end summation
} thread_args;

/**
 * Each thread calls this. Computes a partial sum: begin + begin+1 + ... + end
 * @param *arguments a pointer to a thread_args struct
 *
 */
void *partial_sum(void *args)
{
  // cast input as struct thread_args
  thread_args *params = (thread_args *)args;

  long local_sum = 0; // holds the sum for "chunk" of numbers (begin + ... + end)

  long i;
  for (i = params->begin; i <= params->end; i++)
  {
    local_sum += i;
  }

  // store in global shared array
  partial_sums[params->tid] = local_sum;
  return NULL;
}

/**
 * Main function
 */
int main()
{
  double start = rtclock(); // start stopwatch

  long finalSum = 0;

  // allocate space to hold threads
  pthread_t threads[NUM_THREADS];

  // prepare threads
  long i;
  thread_args args[NUM_THREADS];
  for (i = 0; i < NUM_THREADS; i++)
  {
    // prepare arguments for a thread
    args[i].tid = i;
    args[i].begin = i * N / NUM_THREADS + 1;
    args[i].end = (i + 1) * N / NUM_THREADS;

    // fire off a thread
    pthread_create(&threads[i], NULL, partial_sum, &args[i]);
  }

  // reap threads, collect each partially computed sum
  for (i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(threads[i], NULL);
    finalSum += partial_sums[i];
  }

  double end = rtclock(); // end stopwatch

  printf("Final Sum = %ld\n", finalSum);
  printf("Time: %.6f sec\n", ((end - start)));

  return 0;
}